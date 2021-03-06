#include <gamelib.h>

// player
byte playerX = 4;
byte playerY = 4;
int playerXnew = playerX;
int playerYnew = playerY;
byte playerCoins = 0;
byte playerHealth = 100;
byte playerAttack = 10;

// fight
byte currentEnemy;
byte whoseMove;
byte lastAttack;

// bitmaps
static unsigned char playerBits[2][8] = { 
  { 0x3c, 0x3c, 0x99, 0x7e, 0x3c, 0x3c, 0x7e, 0x81 },
  { 0x3c, 0x3c, 0x18, 0x7e, 0xbd, 0x3c, 0x7e, 0x81 }
};
static unsigned char wallBits[] = { 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa, 0xff, 0xaa };
static unsigned char coinBits[] = { 0x00, 0x18, 0x24, 0x5a, 0x5a, 0x24, 0x18, 0x00 };
static unsigned char enemyBits[2][8] = { 
  { 0x24, 0x7e, 0x5a, 0xff, 0x42, 0x5a, 0x7e, 0x42 },
  { 0x42, 0x7e, 0x5a, 0x7e, 0xc3, 0x5a, 0x7e, 0x42 }
};
static unsigned char doctorBits[] = { 0x00, 0x18, 0x18, 0x7e, 0x7e, 0x18, 0x18, 0x00 };
  
/**
 * 0 menu
 * 1 game (map)
 * 2 fight
 * 8 gameover (win)
 * 9 gameover (lose)
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
  {0, 0, 3, 3},
  {0, 1, 6, 6},
  {1, 0, 4, 3},
  {0, 1, 2, 6},
};
const byte coinsQuantity = sizeof(coins) / sizeof(coins[0]);

//enemies - mapy, mapx, y, x, health, attack
byte enemies[][6] =
{
  {0, 0, 4,10, 100, 5},
  {0, 0, 6, 5, 100, 6},
  {1, 1, 3, 4, 100, 7},
  {0, 1, 5, 4, 100, 4}
};
const byte enemiesQuantity = sizeof(enemies) / sizeof(enemies[0]);

//doctors - mapy, mapx, y, x, health
byte doctors[][5] =
{
  {0, 0, 3, 6, 50},
  {0, 1, 2, 3, 35},
  {1, 1, 6, 7, 35}
};
const byte doctorsQuantity = sizeof(doctors) / sizeof(doctors[0]);

/* start ------------------------------------------------------------------- */
void setup(void)
{
  initGame(INIT_ALL);  
  display.setFont(u8g2_font_5x7_tf);

  loadMap(mapY, mapX);
}

/* loop -------------------------------------------------------------------- */
void loop(void) {
  // switch between menu and game
  if (buttonPressed(START_BUTTON)) {
    if (stage == 1) {
      stage = 0;
    } else if(stage == 0) {
      stage = 1;
    }
  }

  // stage 2? fight? action button
  if (stage == 2) {
    fight();
  }

  // stage 1? he can move
  if (stage == 1) {
    movement();
  }  

  //finish? win
  if (coinsQuantity == playerCoins) {
    stage = 8;
  }

  // finish? lose
  if (playerHealth == 0) {
    stage = 9;
  }

  //draw everything
  pictureLoop();
}
