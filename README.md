# DIY-Arduino-Handheld-Game-Console

## Uploading games to console

### Option #1 (recommended) using our upload script

This option is the fastest way to get games to your game handheld and play!!

1. Download latest release here ... and extract it somewhere
2. Install USB driver - run arduino/drivers/CH341SER/SETUP.EXE
3. Connect your game console to PC
4. Run game-uploader.exe

### Option #2 (advanced) using your own installed Arduino IDE

This option is for those of you who want to see (and maybe edit) the source code of games and also create your own games!

1. Install Arduino IDE from https://www.arduino.cc/en/main/software
2. Install U8G2 Library via Library Manager directly in the IDE
3. Copy "src/gamelib" folder to your Arduino data path, for example: %userprofile%\documents\Arduino\libraries\gamelib
4. Install USB driver CH341 https://github.com/himalayanelixir/Arduino_USB_Drivers
3. Restart Arduino IDE
4. Load some game from src/games and upload it to your game console

## Build setup instructions (developers only)

1. Place Arduino IDE folder content to dist/arduino
2. Place CH341 driver folder content to dist/arduino/drivers/CH341SER
3. Place U8g2 library to dist/arduino/portable/sketchbook/libraries https://github.com/olikraus/u8g2
4. Run build.cmd
5. Now dist folder contains everything you need

## External Links

* YouTube Channel
https://www.youtube.com/playlist?list=PLZWNQlcHslXWuSwxoAaJYrSB9fYc1FXUI
* Official Online Store
https://www.bastlime.eu
