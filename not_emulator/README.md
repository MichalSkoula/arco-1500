# not_emulator - the emulator for ARCO 1500 game console

## Requirements
* Linux
  * Fedora - dnf install gcc-c++ SDL2 SDL2-devel SDL2_ttf SDL2_ttf-devel
  * Ubuntu - apt-get install gcc libsdl2-dev libsdl2-ttf-dev

## Optional
* Arduino IDE (preferable portable) in /arduino folder with gamelib (ours) and U8G2 libraries

## Usage
* ./build_all.sh
* cd bin
* ./game_name (for example ./the_pong)
