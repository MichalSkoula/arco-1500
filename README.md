# ARCO 1500 - DIY Arduino Game Console

## Uploading games to console

### Option #1 (recommended) using our upload script

This option is the fastest way to get games to your game handheld and play!!

1. Download latest release here https://github.com/MichalSkoula/arco-1500/releases and extract it somewhere
2. Install USB driver - run arduino/drivers/CH341SER/SETUP.EXE
3. Connect your game console to PC
4. Run game_uploader/game_uploader.exe

### Option #2 (advanced) using your own installed Arduino IDE

This option is for those of you who want to see (and maybe edit) the source code of games and also create your own games!

1. Install Arduino IDE from https://www.arduino.cc/en/main/software
2. Install U8G2 Library via Library Manager directly in the IDE
3. Copy "arduino/portable/sketchbook/libraries/gamelib" folder to your Arduino data path, for example: %userprofile%\documents\Arduino\libraries\gamelib
4. Install USB driver CH341 https://github.com/himalayanelixir/Arduino_USB_Drivers
5. Restart Arduino IDE and run some games from games directory

## Build setup instructions (developers only)

1. Place Arduino IDE folder content to /arduino
2. Place CH341 driver folder content to /arduino/drivers/CH341SER
3. Place U8g2 library to /arduino/portable/sketchbook/libraries https://github.com/olikraus/u8g2

## External Links

* YouTube Channel
https://www.youtube.com/playlist?list=PLZWNQlcHslXWuSwxoAaJYrSB9fYc1FXUI
* Official Online Store
https://www.bastlime.eu
