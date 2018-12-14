rem delete old dist folder and files
del /s /f /q dist\games
for /f %%f in ('dir /ad /b dist\games') do (
    rd /s /q dist\games\%%f 
)

rem copy new game files
echo f | xcopy src\games dist\games /s /e /y

rem copy upload script
echo f | xcopy src\upload_game.bat dist\upload_game.bat /s /e /y

rem copy gamelib to arduino ide
echo f | xcopy src\gamelib dist\arduino\portable\sketchbook\libraries\gamelib\ /s /e /y

echo done

pause
