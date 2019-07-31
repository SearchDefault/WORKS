import speech_recognition as sr
import pyaudio
from espeak import espeak
import sys
import webbrowser as wb

def talk ( words ):
	print ( words )
	espeak.synth ( words )

def command ():
    rec = sr.Recognizer ()

    with sr.Microphone () as sourse:
        print ( "Say something:" )
        rec.pause_threshold = 1
        rec.adjust_for_ambient_noise ( sourse, duration = 1 )
        audio = rec.listen ( sourse )

    try:
        line = rec.recognize_google ( audio ).lower()
        print ( "You say: " + line )

    except sr.UnknownValueError:
        talk ( "I'm not understand you" )
        line = command ()

    return line

def make ( line ):
    if "open website" in line:
        talk ( "One second" )
        url = "https://google.com"
        wb.open ( url )

    elif "adult films" in line:
        talk ( "okey bad boy" )
        url = "http://porno365.cc"
        wb.open ( url )

    elif "exit" in line or "stop" in line:
        talk ( "I exit now" )
        sys.exit ()

    elif "name" in line:
        talk ( "My name Kate!" )

if __name__ == "__main__":
    while True:
        make ( command () )
