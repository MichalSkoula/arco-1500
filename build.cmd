@echo off

echo DIY Arduino Handheld Game Console Building Software
echo[ 

echo Creating dist folder
mkdir dist
echo[ 

echo Checking if Arduino IDE is there
IF EXIST dist\arduino (
    echo Ok 
    echo[
) ELSE (
    echo You must place Arduino IDE portable into dist folder
    pause
    exit
)

echo Checking if U8g2 is there
IF EXIST dist\arduino\portable\sketchbook\libraries\U8g2 (
    echo Ok 
    echo[
) ELSE (
    echo You must place U8g2 library into dist\arduino\portable\sketchbook\libraries\ folder
    pause
    exit
)

echo Deleting old games
del /s /f /q dist\games > NUL
for /f %%f in ('dir /ad /b dist\games') do (
    rd /s /q dist\games\%%f 
)
echo[ 

echo Deleting old gamelib
del /s /f /q dist\arduino\portable\sketchbook\libraries\gamelib > NUL
echo[ 

echo Copying new games
echo f | xcopy src\games dist\games /s /e /y /i /q
echo[ 

echo Copying gamelib to Arduino IDE
echo f | xcopy src\gamelib dist\arduino\portable\sketchbook\libraries\gamelib\ /s /e /y /i /q
echo[ 

echo Copying upload script
echo f | xcopy src\gameuploader\DIY-game-uploader\bin\Release\DIY-game-uploader.exe dist\game-uploader.exe /s /e /y /i /q
echo[ 

echo Done

pause
