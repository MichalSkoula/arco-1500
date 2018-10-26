#include <U8g2lib.h>
#include <Keypad.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// buttons
const byte startButton = 13;
byte startButtonState = 0;
byte lastStartButtonState = 0;

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

//player
byte playerX;
byte playerY;
int playerXnew;
int playerYnew;

/**
 * 0 menu
 * 1 game
 * 2 gameover
 */
byte stage;

/**
 * map
 * 1 free place 
 * 2 wall
 */
byte mapX;
byte mapY;
const byte MAP_SIZE = 2;
const byte SCREEN_ROWS = 8;
const byte SCREEN_COLS = 12;
const byte TILE_SIZE = 8; //in px
const byte maps[MAP_SIZE][MAP_SIZE][SCREEN_ROWS][SCREEN_COLS] PROGMEM = 
{
  {
    {
      {2,2,2,2,2,2,2,2,2,2,2,2},
      {2,1,1,2,2,1,2,2,2,1,1,2},
      {2,1,1,1,2,1,1,1,1,1,1,2},
      {2,2,1,2,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,1,1},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,1,2,2}
    },
    {
      {2,2,2,2,2,2,2,2,2,2,2,2},
      {2,1,2,2,2,2,2,2,2,1,1,2},
      {2,1,1,1,1,1,1,1,1,1,1,2},
      {2,1,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {1,1,1,1,1,1,2,2,1,2,2,2},
      {2,2,2,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,1,2,2}
    }
  },
  {
    {
      {2,2,2,2,2,2,2,2,2,1,2,2},
      {2,1,1,2,2,1,2,2,2,1,1,2},
      {2,1,1,1,2,1,1,1,1,1,1,1},
      {2,2,1,2,1,1,1,1,1,1,1,1},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,2,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,2,2,2}
    },
    {
      {2,2,2,2,2,2,2,2,2,1,2,2},
      {2,1,2,2,2,2,2,2,2,1,1,2},
      {1,1,1,1,1,1,1,1,1,1,1,2},
      {1,1,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,2,2},
      {2,2,2,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,2,2,2}
    }
  }
};
byte currentMap[SCREEN_ROWS][SCREEN_COLS];

//coins - mapy, mapx, y, x
byte defaultCoins[][4] =
{
  {0,0,3,3},
  {0,0,3,6},
  {1,0,4,3},
  {0,1,2,6},
};

void setDefaultValues()
{
  playerX = 4;
  playerY = 4;
  playerXnew = playerX;
  playerYnew = playerY;

  mapX = 0;
  mapY = 0;
  loadMap(mapY, mapX);
  
  stage = 0;
}

void loadMap(byte mapY, byte mapX)
{
  // load map from flash memory to ram
  for (int y = 0; y < SCREEN_ROWS; y++) {
    for (int x = 0; x < SCREEN_COLS; x++) {
      currentMap[y][x] = pgm_read_byte(&(maps[mapY][mapX][y][x]));
    }
  }

  // add coins
  for (int coinIndex = 0; coinIndex < sizeof(defaultCoins) / sizeof (defaultCoins[0]); coinIndex++) {
    if (defaultCoins[coinIndex][0] == mapY && defaultCoins[coinIndex][1] == mapX) {
      currentMap[defaultCoins[coinIndex][2]][defaultCoins[coinIndex][3]] = 3;
    }
  }
}

void setup(void)
{
  // activate buttons
  pinMode(startButton, INPUT);

  // set font globally
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x12_tf);

  // start serial monitor
  Serial.begin(9600);

  setDefaultValues();
}

void loop(void) {
  // switch between menu and game
  startButtonState = digitalRead(startButton);
  if (startButtonState != lastStartButtonState && startButtonState == HIGH) {
    if (stage == 1 || stage == 2) {
      stage = 0;
    } else if(stage == 0) {
      stage = 1;
    }
  }
  lastStartButtonState = startButtonState;
  
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
    // on the edge => change map?
    bool changeMap = false;
    if (playerYnew == SCREEN_ROWS) {
      mapY++;
      playerYnew = 0;
      changeMap = true;
    } else if (playerYnew == -1) {
      mapY--;
      playerYnew = SCREEN_ROWS - 1;
      changeMap = true;
    } else if (playerXnew == SCREEN_COLS) {
      mapX++;
      playerXnew = 0;
      changeMap = true;
    } else if (playerXnew == -1) {
      mapX--;
      playerXnew = SCREEN_COLS - 1;
      changeMap = true;
    }
    if (changeMap) {
      loadMap(mapY, mapX);
    }
    
    // walk
    if (currentMap[playerYnew][playerXnew] == 1) {
      playerX = playerXnew;
      playerY = playerYnew;
    }
    
    //pick coin and walk
    if (currentMap[playerYnew][playerXnew] == 3) {
      playerX = playerXnew;
      playerY = playerYnew;
      currentMap[playerYnew][playerXnew] = 1;

      //finish? reset
      /*
      if (defaultCoinsQuantity == playerCoins) {
        setDefaultValues();
        stage = 2;
      }*/
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
        drawMap();
        drawSidebar();
        break;
      case 2:
        drawGameOver();
        break;
      default:
        break;
    }
  } while ( u8g2.nextPage() );

  // rebuild the picture after some delay
  delay(10);
}

void drawMenu()
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //logo
  u8g2.setCursor(18, 15);
  u8g2.print("TRAIN LEGION v1");

  //text
  u8g2.setCursor(20, 50);
  u8g2.print("press the start");
}

void drawGameOver()
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //logo
  u8g2.setCursor(20, 15);
  u8g2.print("GAME OVER");

  //text
  u8g2.setCursor(20, 50);
  u8g2.print("press the start");
}

void drawSidebar()
{
  //score
  u8g2.setCursor(97, 10);
  u8g2.print("coins");
  u8g2.setCursor(97, 20);
  //u8g2.print(String(playerCoins) + "/" + String(defaultCoinsQuantity));

  //coordinates
  //u8g2.setCursor(97, 40);
  //u8g2.print(String(playerX) + ":" + String(playerY));

  //rectangles
  //u8g2.drawFrame(0, 0, 96, 64);
  u8g2.drawFrame(96, 0, 32, 64);

  //minimap
  u8g2.drawFrame(100, 44, 24, 16);
  u8g2.drawPixel(100 + mapX * SCREEN_COLS + playerX, 44 + mapY * SCREEN_ROWS + playerY);
}

void drawMap()
{ 
  int offsetX = playerX - SCREEN_COLS / 2;
  int offsetY = playerY - SCREEN_ROWS / 2;

  //player - always centered
  u8g2.drawBox((playerX) * TILE_SIZE, (playerY) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

  //map
  for (int y = 0; y < SCREEN_ROWS; y++){
    for (int x = 0; x < SCREEN_COLS; x++){
      
      if (currentMap[y][x] == 2) {
        // normal wall
        u8g2.drawFrame(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
      } else if (currentMap[y][x] == 3) {
        // coin
        u8g2.drawDisc(x * TILE_SIZE + TILE_SIZE / 2, y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 2, U8G2_DRAW_ALL);
      }
    }
  }
}
