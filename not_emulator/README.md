# not_emulator - the emulator for ARCO 1500 game console

## Requirements
* Linux
  * Fedora - dnf install gcc-c++ SDL2 SDL2-devel SDL2_ttf SDL2_ttf-devel
  * Ubuntu - apt-get install gcc libsdl2-dev libsdl2-ttf-dev
* Windows (Experimental - Bitmaps/XBM in games can cause some trouble)
  * Download and install MSYS2 MinGW 64bit from here: https://www.msys2.org/
  * Start MSYS2 MinGW and use it as terminal for following:
  * Update: pacman -Syu
  * Install SDL2 stuff: pacman -S git mingw-w64-x86_64-toolchain mingw64/mingw-w64-x86_64-SDL2 mingw64/mingw-w64-x86_64-SDL2_mixer mingw64/mingw-w64-x86_64-SDL2_image mingw64/mingw-w64-x86_64-SDL2_ttf mingw64/mingw-w64-x86_64-SDL2_net mingw64/mingw-w64-x86_64-cmake make

## Optional
* Arduino IDE (preferable portable) in /arduino folder with gamelib (ours) and U8G2 libraries

## Usage

game - name of the game (eg. the_pong)

* ./build_all.sh (or ./build.sh game)
* cd bin
* ./game 
