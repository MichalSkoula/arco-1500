@echo off
set /p com_number="Insert COM port number and press [ENTER]: "
set /p game="Insert game title you want to play and press [ENTER]: "

arduino_debug.exe --board arduino:avr:nano:cpu=atmega328old --port COM%com_number% --upload games/%game%/%game%.ino

echo done

pause
