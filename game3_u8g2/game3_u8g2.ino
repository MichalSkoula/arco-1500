#include <U8g2lib.h>
#include <U8x8lib.h>

#include <Key.h>
#include <Keypad.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

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
const byte WORLD_ROWS = 2;
const byte WORLD_COLS = 2; 
const byte MAP_ROWS = 8;
const byte MAP_COLS = 12;
byte maps[WORLD_ROWS][WORLD_COLS][MAP_ROWS][MAP_COLS] = 
{
  {
    {
      {2,2,2,2,2,2,2,2,2,2,2,2},
      {2,1,1,2,2,1,2,2,2,1,1,2},
      {2,1,1,1,2,1,1,1,1,1,1,2},
      {2,2,1,2,1,3,1,1,1,1,1,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,2,1},
      {2,2,3,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,1,2,2}
    },
    {
      {2,2,2,2,2,2,2,2,2,2,2,2},
      {2,1,2,2,2,2,2,2,2,1,1,2},
      {2,1,1,1,1,1,1,1,1,1,1,2},
      {2,1,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,3,1,1,1,1,3,1,1,2},
      {1,2,1,1,1,1,2,2,1,2,2,2},
      {2,2,2,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,1,2,2}
    }
  },
  {
    {
      {2,2,2,2,2,2,2,2,2,1,2,2},
      {2,1,1,2,2,1,2,2,2,1,1,2},
      {2,1,1,1,2,1,1,1,1,1,1,2},
      {2,2,1,2,1,3,1,1,1,1,1,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,2,2},
      {2,2,3,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,2,2,2}
    },
    {
      {2,2,2,2,2,2,2,2,2,1,2,2},
      {2,1,2,2,2,2,2,2,2,1,1,2},
      {2,1,1,1,1,1,1,1,1,1,1,2},
      {2,1,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,3,1,1,1,1,3,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,2,2},
      {2,2,2,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,1,2,2}
    }
  }
};

//0 menu, 1 game
int stage = 0;
int current_map[2] = {0, 0};

void setup(void)
{
  // activate buttons
  pinMode(startButton, INPUT);

  // set font globally
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x12_tf);

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
    if (maps[current_map[0]][current_map[1]][playerYnew][playerXnew] == 1) {
      playerX = playerXnew;
      playerY = playerYnew;
    }
    //pick coin and walk
    if (maps[current_map[0]][current_map[1]][playerYnew][playerXnew] == 3) {
      playerX = playerXnew;
      playerY = playerYnew;
      playerScore++;
      maps[current_map[0]][current_map[1]][playerYnew][playerXnew] = 1;
    }
  }
  
  // picture loop
  u8g2.firstPage();
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
  } while ( u8g2.nextPage() );

  // rebuild the picture after some delay
  delay(10);
}

void drawMenu(void)
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //logo
  u8g2.setCursor(18, 15);
  u8g2.print("TRAIN LEGION v0");

  //text
  u8g2.setCursor(20, 50);
  u8g2.print("press the start");
}

void drawSidebar()
{
  u8g2.setCursor(97, 15);
  u8g2.print("score");
  
  u8g2.setCursor(97, 35);
  u8g2.print(playerScore);
  
  u8g2.drawFrame(0, 0, 128, 64);
}

void drawGame(void)
{ 
  //player
  u8g2.drawBox(playerX * tileSize, playerY * tileSize, tileSize, tileSize);
 
  //map
  for (int y=0; y < MAP_ROWS; y++){
    for (int x=0; x < MAP_COLS; x++){
      
      //wall
      if (maps[current_map[0]][current_map[1]][y][x] == 2) {
        u8g2.drawFrame(x * tileSize, y * tileSize, tileSize, tileSize);
      }
      //coin
      if (maps[current_map[0]][current_map[1]][y][x] == 3) {
        u8g2.drawDisc(x * tileSize + tileSize / 2, y * tileSize + tileSize / 2, tileSize / 2, U8G2_DRAW_ALL);
      }
    }
  } 
}
