#include <ESP8266WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>

#include <MPU6050.h>

#define PORT 9001
#define DEVICE 1

MPU6050 mpu;

String DataSent;
int16_t ax, ay, az;
int16_t gx, gy, gz;
int ResetCounter;

void setup()
{
  int status;
  Serial.begin(115200);
  delay(10);
  
  Wire.begin();
  Wire.setClock(400000L);
  
  mpu.initialize();
  mpu.setFullScaleAccelRange(MPU6050_IMU::MPU6050_ACCEL_FS_4);
  mpu.setFullScaleGyroRange(MPU6050_IMU::MPU6050_GYRO_FS_500);
  
  mpu.setXAccelOffset(1063);
  mpu.setYAccelOffset(-2961);
  mpu.setZAccelOffset(1819);
  mpu.setXGyroOffset(-61);
  mpu.setYGyroOffset(81);
  mpu.setZGyroOffset(-76);
  
  delay(100);
  
//  status = WiFi.begin("HotSpot", "qwerty1234");
  status = WiFi.begin("Alex", "26082000");
  
  Serial.println();
  Serial.print("Waiting WiFi");
  status = WiFi.waitForConnectResult();
  while (status != WL_CONNECTED)
  {
    Serial.print(".");
    delay(50);
  }
  
  Serial.println("Connected");
  Serial.print("MAC Addr: ");
  Serial.println(WiFi.macAddress());
  Serial.print("IP Addr: ");
  Serial.println(WiFi.localIP());
  Serial.print("Subnet: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("DNS Addr: ");
  Serial.println(WiFi.dnsIP());
  Serial.print("Channel: ");
  Serial.println(WiFi.channel());
  Serial.print("Status: ");
  Serial.println(WiFi.status());
  }

void loop()
{
  WiFiClient client;
  
  int8_t start = 0;
  const uint16_t port = PORT;
//  const char * host = "192.168.43.60";
  const char * host = "192.168.1.39";
  
  Serial.print("Connecting to: ");
  Serial.println(host);
  
  if (!client.connect(host, port))
  {
    Serial.println("Connection failed");
    delay(500);
  
    if (ResetCounter > 3)
      ESP.reset();
      
    ResetCounter++;
    return;
  }

  Serial.println("Waiting start");
  while ( client.connected() && !start )
  {
    String line = client.readStringUntil('\n');
    Serial.println(line.length());
    start = line[4] - '0';
    Serial.println(start);
    delay(500);
  }

  int start_measure = 0;
  int start_micros = micros();
  while ( client.connected() )
  {
    if ( start == 1 )
    {
      start_measure = micros();
      int current_time = start_measure - start_micros;
      if ( ( current_time % 1000 ) == 0 )
      {
        int scan_i2c = micros();
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        Serial.print ( micros() - scan_i2c );
        DataSent = (String() + "{\"D\":" + DEVICE + ",\"T\":" + current_time + ",\"G\":{\"X\":" + gx + ",\"Y\":" + gy + ",\"Z\":" + gz + "},\"A\":{\"X\":" + ax + ",\"Y\":" + ay + ",\"Z\":" + az + "}}" );
//        sprintf ( DataSent, "{D:%d,T:%d,G:{X:%d,Y%d,Z:%d},A:{X:%d,Y:%d,Z:%d}}", DEVICE, start_measure - start_micros, gx, gy, gz, ax, ay, az );
//        Serial.println(DataSent);
        scan_i2c = micros ();
        client.println(DataSent);
        Serial.println ( "\t" + String( micros () - scan_i2c ) );
//          char data[100];
//          sprintf ( data, "{D:23432423,T:%d,G:{X:235352,Y325325235,Z:235235},A:{X:23523523,Y:3532525,Z:34353}}\n", current_time );
//          client.write ( data, strlen (data) );
      }
    }
  }
  delayMicroseconds(1);
  start = 0;
  Serial.println("End Program");
  client.stop();
}
