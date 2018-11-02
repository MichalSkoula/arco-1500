#include <U8g2lib.h>
#include <Keypad.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// buttons
const byte startButton = 13;
byte startButtonState = 0;
byte lastStartButtonState = 0;

// keypad
const byte KEYPAD_ROWS = 1; //four rows
const byte KEYPAD_COLS = 4; //three columns
char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1','2','3','4'},
};
byte rowPins[KEYPAD_ROWS] = {2}; //connect to the row pinouts of the keypad
byte colPins[KEYPAD_COLS] = {6,5,4,3}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS );

// player
byte playerX = 4;
byte playerY = 4;
int playerXnew = playerX;
int playerYnew = playerY;
byte playerCoins = 0;
byte playerHealth = 100;

// bitmaps
static unsigned char playerBits[] = { 0x3c, 0x3c, 0x99, 0x7e, 0x3c, 0x3c, 0x7e, 0x81 };
static unsigned char wallBits[] = { 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa };
static unsigned char coinBits[] = { 0x3c, 0x66, 0xc3, 0x99, 0x99, 0xc3, 0x66, 0x3c };
static unsigned char enemyBits[2][8] = { 
  { 0x24, 0x7e, 0x5a, 0xff, 0x42, 0x5a, 0x7e, 0x42 },
  { 0x42, 0x7e, 0x5a, 0x7e, 0xc3, 0x5a, 0x7e, 0x42 }
};
  
/**
 * 0 menu
 * 1 game
 * 2 gameover (win)
 * 3 gameover (lose)
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
      {2,1,1,1,2,1,1,1,1,1,1,1},
      {2,2,1,1,1,1,1,1,1,1,1,1},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,1,1,1,1,2,2,1,2,1,1},
      {2,2,1,1,1,1,1,1,1,1,1,2},
      {2,2,2,2,2,2,2,2,2,1,2,2}
    },
    {
      {2,2,2,2,2,2,2,2,2,2,2,2},
      {2,1,2,2,2,2,2,2,2,1,1,2},
      {1,1,1,1,1,1,1,1,1,1,1,2},
      {1,1,1,1,1,1,1,1,1,1,1,2},
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

//enemies - mapy, mapx, y, x
byte enemies[][4] =
{
  {0,0,4,10},
  {0,0,6,5},
  {1,1,3,4},
  {0,1,5,4},
};
const byte enemiesQuantity = sizeof(enemies) / sizeof(enemies[0]);

/* start ------------------------------------------------------------------- */
void setup(void)
{
  // activate buttons
  pinMode(startButton, INPUT);

  // set font globally
  u8g2.begin();
  u8g2.setFont(u8g2_font_5x7_tf);

  // serial
  Serial.begin(9600);
  
  // random seed
  randomSeed(analogRead(0));

  // load map 
  loadMap(mapY, mapX);
}

/* loop -------------------------------------------------------------------- */
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

  // which stage?
  if (stage == 1) {
    //potential movement
    movement();
  }  

  //finish? reset
  if (coinsQuantity == playerCoins) {
    stage = 2;
  }

  // finish? reset
  if (playerHealth <= 0) {
    stage = 3;
  }

  //draw everything
  pictureLoop();
}
