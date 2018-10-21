#include <Key.h>
#include <Keypad.h>
#include "U8glib.h"

// Display which does not send AC
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

// constants
const int startButton = 13;
const int tileSize = 8;
const int screenWidth = 128;
const int screenHeight = 64;

int startButtonState = 0;
int lastStartButtonState = 0;

//keypad
const byte KEYPAD_ROWS = 4; //four rows
const byte KEYPAD_COLS = 3; //three columns
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[KEYPAD_ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[KEYPAD_COLS] = {6,7,8}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS );

//hero
int playerX = screenWidth / tileSize / 2;
int playerY = screenHeight / tileSize / 2;
int playerXnew = playerX;
int playerYnew = playerY;
int playerScore = 0;

/**
 * map
 * 1 free place 
 * 2 wall
 * 3 coin
 */
const int MAP_ROWS = 8;
const int MAP_COLS = 12;
int maps[2][MAP_ROWS][MAP_COLS] = {
  {
    {2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,1,1,2},
    {2,2,2,2,2,1,1,1,1,1,1,2},
    {2,2,2,2,1,3,1,1,1,1,1,2},
    {2,2,2,1,1,1,1,1,1,1,1,2},
    {2,2,2,1,1,1,2,2,1,2,2,2},
    {2,2,2,1,1,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,2,2,2,1,2,2},
  },
  {
    {2,2,2,2,2,2,2,2,2,1,2,2},
    {2,1,2,2,2,2,2,2,2,1,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,2},
    {2,2,1,3,1,1,1,1,3,1,1,2},
    {2,2,1,1,1,1,2,2,1,2,2,2},
    {2,2,2,1,1,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,2,2,2,2,2,2},
  }
};

//0 menu, 1 game
int stage = 0; 
int current_map = 0;

void setup(void)
{
  // activate buttons
  pinMode(startButton, INPUT);

  // set font globally
  u8g.setFont(u8g_font_6x12);

  // start serial monitor
  Serial.begin(9600);
}

void loop(void) {
  // switch between menu and game
  startButtonState = digitalRead(startButton);
  if (startButtonState != lastStartButtonState && startButtonState == HIGH) {
    stage = !stage;
  }
  lastStartButtonState = startButtonState;
  //Serial.println(startButtonState);
  
  // keypad movement
  char key = keypad.getKey();
  if (key == '2'){
    playerYnew = playerY - 1;
    playerXnew = playerX;
  } else if (key == '8'){
    playerYnew = playerY + 1;
    playerXnew = playerX;
  } else if (key == '4'){
    playerXnew = playerX - 1;
    playerYnew = playerY;
  } else if (key == '6'){
    playerXnew = playerX + 1;
    playerYnew = playerY;
  }
  // key pressed
  if (strlen(key)) {
    //walk
    if (maps[current_map][playerYnew][playerXnew] == 1) {
      playerX = playerXnew;
      playerY = playerYnew;
    }
    //pick coin and walk
    if (maps[current_map][playerYnew][playerXnew] == 3) {
      playerX = playerXnew;
      playerY = playerYnew;
      playerScore++;
      maps[current_map][playerYnew][playerXnew] = 1;
    }
  }
  
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
        drawSidebar();
        break;
      default:
        break;
    }
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(10);
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

void drawSidebar()
{
  //u8g.setPrintPos(96, 35);
 // u8g.print(playerScore);
 u8g.drawFrame(0, 0, 128, 64);
}

void drawGame(void)
{
  //player
  u8g.drawBox(playerX * tileSize, playerY * tileSize, tileSize, tileSize);
  
  //map
  for (int y=0; y <= MAP_ROWS; y++){
    for (int x=0; x <= MAP_COLS; x++){
      //wall
      if (maps[current_map][y][x] == 2) {
        u8g.drawFrame(x * tileSize, y * tileSize, tileSize, tileSize);
      }
      //coin
      if (maps[current_map][y][x] == 3) {
        u8g.drawCircle(x * tileSize + tileSize / 2, y * tileSize + tileSize / 2, tileSize / 2);
      }
    }
  }
}
