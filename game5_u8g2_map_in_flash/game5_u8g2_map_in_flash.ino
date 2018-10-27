#include <U8g2lib.h>
#include <Keypad.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// buttons
const byte startButton = 13;
byte startButtonState = 0;
byte lastStartButtonState = 0;

// keypad
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

// player
byte playerX = 4;
byte playerY = 4;
int playerXnew = playerX;
int playerYnew = playerY;
int playerCoins = 0;

// images
static unsigned char playerBits[] = { 0x3c, 0x3c, 0x99, 0x7e, 0x3c, 0x3c, 0x7e, 0x81 };
static unsigned char wallBits[] = { 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa };
static unsigned char coinBits[] = { 0x3c, 0x66, 0xc3, 0x99, 0x99, 0xc3, 0x66, 0x3c };
  
/**
 * 0 menu
 * 1 game
 * 2 gameover
 */
byte stage = 0;

/**
 * map
 * 1 free place 
 * 2 wall
 */
byte mapX = 0;
byte mapY = 0;
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
      {2,2,1,1,1,1,1,1,1,1,1,2},
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
      {2,1,1,2,2,1,1,2,2,1,1,2},
      {2,1,1,1,2,1,1,1,1,1,1,1},
      {2,2,1,2,1,1,1,1,1,1,1,1},
      {2,2,1,1,1,1,2,1,1,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,2,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,2,2,2}
    },
    {
      {2,2,2,2,2,2,2,2,2,1,2,2},
      {2,1,1,2,1,2,2,1,2,1,1,2},
      {1,1,1,1,1,2,1,1,1,1,1,2},
      {1,1,1,1,1,2,1,1,1,1,1,2},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,1,2,1,2,2,2},
      {2,2,2,1,1,2,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,2,2,2}
    }
  }
};
byte currentMap[SCREEN_ROWS][SCREEN_COLS];

//coins - mapy, mapx, y, x
byte coins[][4] =
{
  {0,0,3,3},
  {0,0,3,6},
  {1,0,4,3},
  {0,1,2,6},
};
const byte coinsQuantity = sizeof(coins) / sizeof(coins[0]);

/* start ------------------------------------------------------------------- */
void setup(void)
{
  // activate buttons
  pinMode(startButton, INPUT);

  // set font globally
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x12_tf);

  // start serial monitor
  Serial.begin(9600);

  loadMap(mapY, mapX);
}

/* loop ------------------------------------------------------------------- */
void loop(void) {
  // switch between menu and game
  startButtonState = digitalRead(startButton);
  if (startButtonState != lastStartButtonState && startButtonState == HIGH) {
    if (stage == 1) {
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

      //pick coin and walk
      for (int i = 0; i < coinsQuantity; i++) {
        if (coins[i][0] == mapY && coins[i][1] == mapX && coins[i][2] == playerY && coins[i][3] == playerX) {
          playerCoins++;
          coins[i][1] = 99; //haha put it away
  
          //finish? reset
          if (coinsQuantity == playerCoins) {
            stage = 2;
          }
        }
      }
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

// load map from flash memory to ram
void loadMap(byte mapY, byte mapX)
{
  for (byte y = 0; y < SCREEN_ROWS; y++) {
    for (byte x = 0; x < SCREEN_COLS; x++) {
      currentMap[y][x] = pgm_read_byte(&(maps[mapY][mapX][y][x]));
    }
  }
}

/* drawings --------------------------------------------------------------------- */
void drawMenu()
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //logo
  u8g2.setCursor(15, 15);
  u8g2.print("DIY Handheld Game");
  
  //text
  u8g2.setCursor(20, 55);
  u8g2.print("press the start");
}

void drawGameOver()
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //logo
  u8g2.setCursor(20, 15);
  u8g2.print("GAME OVER");
}

void drawSidebar()
{
  //score
  u8g2.setCursor(97, 10);
  u8g2.print("coins");
  u8g2.setCursor(97, 20);
  u8g2.print(String(playerCoins) + "/" + String(coinsQuantity));

  //rectangles
  //u8g2.drawFrame(0, 0, 96, 64);
  u8g2.drawFrame(96, 0, 32, 64);

  //minimap
  u8g2.drawFrame(100, 44, 24, 16);
  u8g2.drawPixel(100 + mapX * SCREEN_COLS + playerX, 44 + mapY * SCREEN_ROWS + playerY);
}

void drawMap()
{ 
  //player - always centered
  //u8g2.drawBox((playerX) * TILE_SIZE, (playerY) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
  u8g2.drawXBM(playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE, playerBits);

  //map
  for (int y = 0; y < SCREEN_ROWS; y++){
    for (int x = 0; x < SCREEN_COLS; x++){
      if (currentMap[y][x] == 2) {
        //u8g2.drawFrame(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        u8g2.drawXBM(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, wallBits);
      }
    }
  }

  //coins
  for (int i = 0; i < coinsQuantity; i++) {
    if (coins[i][0] == mapY && coins[i][1] == mapX) {
      //u8g2.drawDisc(coins[i][3] * TILE_SIZE + TILE_SIZE / 2, coins[i][2] * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE / 2, U8G2_DRAW_ALL);
      u8g2.drawXBM(coins[i][3] * TILE_SIZE, coins[i][2] * TILE_SIZE, TILE_SIZE, TILE_SIZE, coinBits);
    }
  }
}
