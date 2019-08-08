---
layout: default

---

# Develop your own game!

You can develop your own games with just a little knowledge of programming (C++ / Wiring). 

## Hello Arco

There is this game called "Hello Arco" which is an equivalent for classic "Hello World" programs. You can use it as a boilerplate for developing your game.

<img data-src="{{ '/assets/images/hello_arco.png' | prepend: site.baseurl }}" class="img-responsive float-left mr-3 image-border">

The game structure is simple. There must be a folder inside the "games" directory. Then, inside the folder, there must be an .ino file with the same name as folder. This file is the main and only required file. 

You can divide your code into several .ino files, but this is just for clarity.

<div class="clearfix"></div>

## Arduino IDE

You load the main file "hello_arco.ino" into Arduino IDE. But wait, before uploading it to console, you must specify the port number to which your console is connected.

<img data-src=" {{ '/assets/images/arduino_ide_select_port.png' | prepend: site.baseurl }}" class="img-responsive image-border">

<div class="clearfix"></div>

## Gamelib

<img data-src="{{ '/assets/images/gamelib_small.png' | prepend: site.baseurl }}" class="img-responsive float-left mr-3 image-border">

This is our (optional to use) library which can help you create games easily. 

You can find it source files in "arduino/portable/sketchbook/libraries/gamelib".

You can find simple class reference below.

<div class="clearfix"></div>

### Display global object

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

### Sound global object

```cpp
// use it like sound.playTone(200, 200); ...
void playTone(int pitch, int time = 10);
void playSong(Song &song);
```

### Score Table

```cpp
// Create scoreTable object with GID of your game (must be declared in score.h)
ScoreTable<GID_GALAXY_MADNESS> scoreTable;
// use it like scoreTable.addScore(5);
void setScore(score_t value);
void addScore(int value);
void update(); // game over, save score
void draw(); // draw highscore screen
```
### Input class

```cpp
// use it like buttonDown(RIGHT_BUTTON);
bool buttonDown(byte button);
bool buttonPressed(byte button);
```
### Gamelib class
```cpp
// call this in "setup" function
void initGame(INIT_ALL);
void softReset();
```

<div class="clearfix"></div>

## Emulator

For Linux users out there, we have an emulator. You can find it in "not_emulator" folder. There is a README.md file with simple instructions on how to use it.

## [<< Make](/make.html) | Develop | [Play >>](/play.html)
