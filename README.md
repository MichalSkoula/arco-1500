# DIY-Arduino-Handheld-Game-Console

## Uploading games to console

### Option #1 (recommended, beginner) using our upload script

This option is the fastest way to get games to your game handheld.

1. Download latest release here: ...
2. Extract it somewhere
3. Connect your game console to PC
4. Run upload-game.bat

### Option #2 (advanced) using your own installed Arduino IDE

This option is for those of you who want to see (and maybe edit) the source code of games and also create your own games! You must have Arduino IDE installed and have some experience in programming.

1. Install U8G2 Library via Library Manager directly in IDE
2. Copy "src/gamelib" folder to your Arduino data path, for example: $HOME/Arduino/libraries/gamelib
3. Restart Arduino IDE
4. Load some game from src/games and upload it to your game console

## Build setup instructions (developers only)

* Place Arduino IDE folder content to dist/arduino
* Place U8g2 library to dist/arduino/portable/sketchbook/libraries https://github.com/olikraus/u8g2
* Run build.bat 
* Now dist folder contains everything you need

## External Links

* YouTube Channel
https://www.youtube.com/watch?v=1ha5cjtXs_Q&list=PLZWNQlcHslXWuSwxoAaJYrSB9fYc1FXUI
* Official Online Store
https://www.bastlime.eu
