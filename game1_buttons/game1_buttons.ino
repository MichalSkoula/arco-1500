#include <U8glib.h>

#include "U8glib.h"

// Display which does not send AC
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

// constants
const int startButton = 13;
const int leftButton = 12;
const int rightButton = 11;
const int tileSize = 8;
const int screenWidth = 128;
const int screenHeight = 64;

// buttons
int startButtonState = 0;
int lastStartButtonState = 0;

int leftButtonState = 0;
int lastLeftButtonState = 0;

int rightButtonState = 0;
int lastRightButtonState = 0;

//hero
int playerX = screenWidth / tileSize / 2;
int playerY = screenHeight / tileSize / 2;

int stage = 0; //0 menu, 1 game

void setup(void)
{
  // activate buttons
  pinMode(startButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);

  // set font globally
  u8g.setFont(u8g_font_6x12);

  // start serial monitor
  //Serial.begin(9600);
}

void loop(void) {
  // switch between menu and game
  startButtonState = digitalRead(startButton);
  if (startButtonState != lastStartButtonState && startButtonState == HIGH) {
    stage = !stage;
  }
  lastStartButtonState = startButtonState;
  //Serial.println(startButtonState);
  
  // walk left
  leftButtonState = digitalRead(leftButton);
  if (leftButtonState != lastLeftButtonState && leftButtonState == HIGH) {
    playerX--;
  }
  lastLeftButtonState = leftButtonState;
  //walk right
  rightButtonState = digitalRead(rightButton);
  if (rightButtonState != lastRightButtonState && rightButtonState == HIGH) {
    playerX++;
  }
  lastRightButtonState = rightButtonState;
  
  // picture loop
  u8g.firstPage();
  do {
    //decide what to draw at this iteration
    switch (stage) {
      case 0:
        drawMenu();
        break;
      case 1:
        drawGame();
        break;
      default:
        break;
    }
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(200);
}

void drawMenu(void)
{
  //rectangle
  u8g.drawFrame(0, 0, 128, 64);

  //logo
  u8g.setPrintPos(18, 15);
  u8g.print("TRAIN LEGION v0");

  //text
  u8g.setPrintPos(20, 50);
  u8g.print("press the start");

}

void drawGame(void)
{
  //player
  u8g.drawBox(playerX * tileSize, playerY * tileSize, tileSize, tileSize);
}
