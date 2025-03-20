# ARCO 1500

Build your own 8 bit gaming console based on the Arduino platform. ARCO1500 is an open source, 8 bit DIY gaming console - both software and hardware.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/product.jpg)

## Links
* [YouTube](https://www.youtube.com/playlist?list=PLZWNQlcHslXWuSwxoAaJYrSB9fYc1FXUI)
* [Facebook](https://www.facebook.com/bastlime/)
* [Twitter](https://twitter.com/MichalSkoula)

## 1. Building the console is a breeze. 

Here is a video about how to do it: http://www.youtube.com/watch?v=pl3g7Zw-S20

### Complete set 

The whole set looks like this. You can buy it [here](https://www.bastlime.eu/c/36616-sady) (Czechia, Slovakia, Poland, Hungary).

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/arco1500-set.jpg)

### Connections

On the image below you can see the connections. Please, make sure you connect everything right, otherwise it can be dangerous. Mainly if you switch the + and - pins (VCC and GND).

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/arco-fritzing.png)

## 2. Upload and play games

### Prerequisites

1. Download latest release of ARCO software from [GitHub](https://github.com/MichalSkoula/arco-1500/releases) and extract it somewhere.
2. Install Windows USB driver "arduino/drivers/Arduino_USB_Drivers-master/Windows".

### Use Game Uploader to smoothly upload games to console

This option is the fastest way to get games to your game console and play (Windows only)!

1. Connect your game console to PC with USB cable
2. Run "ARCO1500_Uploader.exe"

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/arco_game_uploader.png)

### Use Arduino IDE

If you:

- cannot (or don't want to) use our upload script
- want to edit games or develop your own
- run Linux / Mac

Then you should use Arduino IDE:

1. Open bundled Arduino IDE "arduino/arduino.exe"
3. Run some games from the "games" directory

## 3. Current game library

### Flappy Cat
Like flappy bird.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/flappy_cat.png)


### Galaxy Madness
Space shooter. You shoot space waste like mad Greta.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/galaxy_madness.png)


### Game of Life
Simulation. Not really a game except you can pause it.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/game_of_life.png)


### The Unfinished RPG project
Four rooms, enemies, medical kits and even a combat system.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/rpg.png)


### Snake
The game with only one button. Which turns left.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/snake.png)


### Space Surfer
Almost 3D space surfing.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/space_surfer.png)


### The Pong
The most classic game of all time.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/the_pong.png)


### Tank92
Like Tank 90.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/games/tank92.png)

## 4. Develop your own games


You can develop your own games with just a little knowledge of programming (C++ / Wiring). 

### Prerequisites

1. Download latest release of ARCO software from [GitHub](https://github.com/MichalSkoula/arco-1500/releases) and extract it somewhere.
2. (Windows only) Install USB driver "arduino/drivers/Arduino_USB_Drivers-master/Windows".

### Hello Arco

There is this game called "Hello Arco" which is an equivalent for classic "Hello World" programs. You can use it as a boilerplate for developing your game.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/hello_arco.png)

The game structure is simple. There must be a folder inside the "games" directory. Then, inside the folder, there must be an .ino file with the same name as folder. This file is the main and only required file. 

You can divide your code into several .ino files, but this is just for clarity.

### Arduino IDE

You load the main file "hello_arco.ino" into Arduino IDE. But wait, before uploading it to console, you must specify the port number to which your console is connected.

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/arduino_ide_select_port.png)

### Gamelib

![](https://github.com/MichalSkoula/arco-1500/blob/master/assets/gamelib_small.png)

This is our (optional to use) library which can help you create games easily. 

You can find it source files in "arduino/portable/sketchbook/libraries/gamelib".

You can find simple class reference below.

#### Display global object

```cpp
// use it like display.drawBigText(5,5, "Hello"); ...
void drawBigText(int x, int y, const String &text);
void drawSmallText(int x, int y, const String &text);
void drawXBM(int x, int y, int w, int h, const uint8_t *data);
void drawVLine(int x, int y, int h);
void drawFrame(int x, int y, int w, int h);
void drawBox(int x, int y, int w, int h);
void drawDisc(int x, int y, int r, uint8_t opt = U8G2_DRAW_ALL);
```

You can use all of U8G2 drawing methods. 

#### Sound global object

```cpp
// use it like sound.playTone(200, 200); ...
void playTone(int pitch, int time = 10);
void playSong(Song &song);
```

#### Score Table

```cpp
// Create scoreTable object with GID of your game (must be declared in score.h)
ScoreTable<GID_GALAXY_MADNESS> scoreTable;
// use it like scoreTable.addScore(5);
void setScore(score_t value);
void addScore(int value);
void update(); // game over, save score
void draw(); // draw highscore screen
```
#### Input class

```cpp
// use it like buttonDown(RIGHT_BUTTON);
bool buttonDown(byte button);
bool buttonPressed(byte button);
```
#### Gamelib class
```cpp
// call this in "setup" function
void initGame(INIT_ALL);
void softReset();
```

### Emulator

We have an emulator for testing games without real console. You can find it in "not_emulator" folder. There is a README.md file with simple instructions on how to use it.

If works perfectly on Linux. On Windows we have alpha version, there are some problems with bitmaps.
