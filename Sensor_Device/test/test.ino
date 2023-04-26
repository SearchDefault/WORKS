#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <brzo_i2c.h>

#define PORT 9001
#define DEVICE 1

enum MPU_REG
{
  MPU_ADDR     =  0x68,
  SDA_PIN      =  D2,
  SCL_PIN      =  D1,
  SMPLRT_DIV   =  0x19,
  USER_CTRL    =  0x6A,
  PWR_MGMT_1   =  0x6B,
  PWR_MGMT_2   =  0x6C,
  CONFIG       =  0x1A,
  GYRO_CONFIG  =  0x1B,
  ACCEL_CONFIG =  0x1C,
  FIFO_EN      =  0x23,
  INT_ENABLE   =  0x38,
  ACCEL_XOUT_H =  0x3B,
  PATH_RESET   =  0x68,
};

// массив данных
// [accX, accY, accZ, temp, gyrX, gyrY, gyrZ]
// acc - ускорение, gyr - угловая скорость, temp - температура (raw)
uint8_t data[14];
char out[100];
int16_t d[7];
float res[7];
uint8_t buffer[20] =
{
  MPU_REG::SMPLRT_DIV,   0x07,
  MPU_REG::PWR_MGMT_1,   0x01,
  MPU_REG::PWR_MGMT_2,   0x00,
  MPU_REG::CONFIG,       0b01,
  MPU_REG::GYRO_CONFIG,  0b01,
  MPU_REG::ACCEL_CONFIG, 0b01,
  MPU_REG::FIFO_EN,      0x01,
  MPU_REG::INT_ENABLE,   0x01,
  MPU_REG::PATH_RESET,   0x00,
  MPU_REG::USER_CTRL,    0x00
};

void setup()
{
  Serial.begin(115200);
  // инициализация
  brzo_i2c_setup(MPU_REG::SDA_PIN, MPU_REG::SCL_PIN, 1000);
  brzo_i2c_start_transaction(MPU_REG::MPU_ADDR, 400);
  brzo_i2c_write(&buffer[0], 2, false);
  brzo_i2c_write(&buffer[2], 2, false);
  brzo_i2c_write(&buffer[4], 2, false);
  brzo_i2c_write(&buffer[6], 2, false);
  brzo_i2c_write(&buffer[8], 2, false);
  brzo_i2c_write(&buffer[10], 2, false);
  brzo_i2c_write(&buffer[12], 2, false);
  brzo_i2c_write(&buffer[14], 2, false);
  brzo_i2c_write(&buffer[16], 2, false);
  brzo_i2c_write(&buffer[18], 2, false);
  brzo_i2c_end_transaction();

  Serial.println ( "Pre connect to wifi" );
  
  int status = WiFi.begin("HotSpot", "qwerty1234");
//  int status = WiFi.begin("Alex", "26082000");
//  int status = WiFi.begin("Bluetooth", "pikabu77");
  status = WiFi.waitForConnectResult();
  while (status != WL_CONNECTED)
    delay(50);
  Serial.println ( "Connected to wifi" );
}
void loop()
{
  WiFiClient client;
  
  int8_t start = 0;
  const uint16_t port = PORT;
//  const char * host = "192.168.5.241";
  const char * host = "192.168.43.60";
//  const char * host = "192.168.1.44";
//  const char * host = "192.168.43.84";

  if (!client.connect(host, port))
  {
    delay(20);
    Serial.print ( "." );
    return;
  }

  client.println("Waiting start");
//  while ( client.connected() && !start )
//  {
//    String line = client.readStringUntil('\n');
//    start = line[4] - '0';
//    delay(500);
//  }
  start = 1;

  int start_measure = 0;
  int start_micros = micros();
  while ( client.connected() )
//  while (1)
  {
    if ( start == 1 )
    {
      start_measure = micros();
      int current_time = start_measure - start_micros;
      if ( ( current_time % 1000 ) < 10 )
      {
        int cur = micros();
        getData();
//        sprintf ( out, "{D:%d,T:%d,G:{X:%d,Y%d,Z:%d},A:{X:%d,Y:%d,Z:%d}}\n", DEVICE, current_time / 1000, d[4], d[5], d[6], d[0], d[1], d[2] );
        sprintf ( out, "%dT%dX%dY%dZ%dX%dY%dZ%d\n", DEVICE, current_time, d[4], d[5], d[6], d[0], d[1], d[2] );
        Serial.print( micros () - cur );
        Serial.print("\t");
        cur = micros();
        client.write( out, strlen(out) );
//        client.flush();
        Serial.println( micros () - cur );
      }
    }
    delayMicroseconds(1);
  }
  start = 0;
  Serial.println("End Program");
  client.stop();
}

uint8_t tmp = MPU_REG::ACCEL_XOUT_H;

void getData()
{
  brzo_i2c_start_transaction(MPU_REG::MPU_ADDR, 400);
  brzo_i2c_write(&tmp, 1, true);
  brzo_i2c_read(data, 14, false);
  brzo_i2c_end_transaction();
  for (byte i = 0, j = 0; i < 14; i += 2, j++)
    d[j] = data[i] << 8 | data[i + 1];
}
