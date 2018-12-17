@echo off

echo DIY Arduino Handheld Game Console Uploading Software
echo[ 

echo Available COM ports:
chgport
set /p com_number="Insert COM port number and press [ENTER]: "
echo[ 

echo Available games:
dir games /AD /B
set /p game="Insert game title you want to play and press [ENTER]: "
echo[ 

".\arduino\arduino_debug.exe" --board arduino:avr:nano:cpu=atmega328old --port COM%com_number% --upload games/%game%/%game%.ino

echo Done

pause
