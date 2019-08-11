import speech_recognition as sr
import pyaudio
from espeak import espeak
import pyttsx3 as tt
import os
import sys
import webbrowser as wb
import time

opts = {
	"names": ( "Kate", "Ann" ),
	"cmds": {
		"ctime": ( "time" ),
		"radio": ( "radio" )
	}
}

def talk ( words ):
    print ( "[log]" + words )
    
    if sys.platform == "linux" or sys.platform == "linux2":
        espeak.set_voice ( "ru+f" )
        espeak.synth ( words )

        while espeak.is_playing ():
            pass

    elif sys.platform == "darwin":
        os.system ( "say " + words )

    elif sys.platform == "win32":
        engine = tt.init ()
        engine.say ( words )
        engine.runAndWait ()
        engine.stop()

def command ():
    rec = sr.Recognizer ()

    with sr.Microphone () as sourse:
        print ( "[log] Скажи что-нибудь:" )
        rec.pause_threshold = 1
        rec.adjust_for_ambient_noise ( sourse, duration = 1 )
        audio = rec.listen ( sourse )

    try:
        line = rec.recognize_google ( audio, language = "ru" ).lower()
        print ( "Ты сказал: " + line )

    except sr.UnknownValueError:
        talk ( "Я тебя не понимаю!" )
        line = command ()

    return line

def make ( line ):
    if "открой браузер" in line:
        talk ( "Одну сикунду" )
        url = "https://google.com"
        wb.open ( url )

    elif "не спишь" in line or "ты тут" in line:
        talk ( "Я не сплю сер!" )
        talk ( "Жду ваших указаний!" )

    elif "пока" in line or "я ухожу" in line:
        talk ( "Доброго вам дня сер!" )
        sys.exit ()

    elif "арбидол" in line:
        talk ( "операция арбидол" )
        url = "http://pornhub.com"
        wb.open ( url )

    elif "имя" in line or "тебя зовут" in line:
        talk ( "Меня зовут Джарвис!" )
    
    elif "открой" and "страницу" in line:
        string = line.split ( " " )
        talk ( "Открываю вам" + string[ len( string ) - 1 ] + "страницу" )
        url = "https://" + string [ len ( string ) - 1 ]
        wb.open ( url )

if __name__ == "__main__":
    while True:
        make ( command () )
