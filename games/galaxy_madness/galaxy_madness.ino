#include <gamelib.h>

// bitmaps
static unsigned char playerBits[] = { 0x18, 0x3c, 0x7e, 0x7e, 0x7e, 0xff, 0xff, 0x66 };
static unsigned char trashSmallBits[3][8] = { 
  { 0x30, 0x3c, 0xfe, 0xfe, 0x7f, 0x3f, 0x7e, 0x30 },
  { 0x10, 0x3c, 0x7e, 0x7e, 0x7f, 0x3f, 0x7c, 0x36 },
  { 0x3c, 0x7e, 0x7f, 0xff, 0xff, 0xff, 0x7e, 0x3e }
};
static unsigned char trashBigBits[3][32] = {
  {
    0x30, 0x3e, 0xfc, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xff, 0x3f, 0xff, 0x3f,
    0xfe, 0x3f, 0xf8, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x1f, 0xfe, 0x3f,
    0xfe, 0x3f, 0xf8, 0x1f, 0xe0, 0x10, 0x00, 0x00
  },
  {
    0x00, 0x38, 0x70, 0x7e, 0xf8, 0x7f, 0xfe, 0x7f, 0xff, 0x3f, 0xfe, 0x3f,
    0xfe, 0x3f, 0xf8, 0x1f, 0xfc, 0x3f, 0xf0, 0x3f, 0xf0, 0x1f, 0xf8, 0x3f,
    0xfe, 0x7f, 0xf8, 0x7e, 0xe0, 0x10, 0x00, 0x00
  },
  { 
    0xe0, 0x03, 0xf8, 0x0f, 0xfc, 0x1e, 0xfe, 0x3b, 0xfe, 0x7f, 0xfe, 0x7d,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff,
    0xfe, 0x7f, 0xfe, 0x7f, 0xfc, 0x3f, 0xf0, 0x07
  }
};
static unsigned char doctorBits[] = { 0x30, 0x10, 0x90, 0xf8, 0x1c, 0x0e, 0x07, 0x03 };
static unsigned char logoBits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x1d, 0x80, 0x0b, 0x3c, 0x80, 0x0b, 0x1f, 0xff, 0xc1, 0x03, 0x00,
   0x00, 0x00, 0x00, 0xc0, 0x1f, 0xf0, 0x1f, 0x3c, 0xf0, 0x1f, 0x1e, 0xef,
   0xe3, 0x03, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0xf0, 0x3f, 0x3c, 0xf0,
   0x3f, 0xbe, 0xcf, 0xf7, 0x01, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0xf8,
   0x7f, 0x3c, 0xf8, 0x7f, 0xbc, 0x87, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
   0xf8, 0x0f, 0xf8, 0x7f, 0x3c, 0xf8, 0x7f, 0xfc, 0x87, 0xff, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf8, 0x00, 0x78, 0x7c, 0x3c, 0x78, 0x7c, 0xf8, 0x03,
   0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x78, 0x7c, 0x3c, 0x78,
   0x7c, 0xf8, 0x03, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x78,
   0x7c, 0x3c, 0x78, 0x7c, 0xf0, 0x01, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x7c, 0xfc, 0xf8, 0x7d, 0x3c, 0xfc, 0x7d, 0xf0, 0x01, 0x3e, 0x00, 0x00,
   0x00, 0x38, 0x00, 0x7c, 0xfc, 0xf8, 0x7d, 0x3c, 0xf8, 0x7d, 0xf8, 0x03,
   0x3e, 0x00, 0x00, 0x00, 0x78, 0x00, 0x7c, 0xfc, 0xfc, 0x7d, 0x3c, 0xf8,
   0x7d, 0xf8, 0x03, 0x3e, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xf8, 0xf0, 0xf8,
   0x7d, 0x7c, 0xf8, 0x7d, 0xfc, 0x07, 0x3e, 0x00, 0x00, 0x00, 0xf0, 0x01,
   0xf8, 0xff, 0xf8, 0x7d, 0xfc, 0xf9, 0x7d, 0xfc, 0x07, 0x3e, 0x00, 0x00,
   0x00, 0xe0, 0x03, 0xf0, 0xff, 0x78, 0x7c, 0xfc, 0x79, 0x7c, 0xbe, 0x0f,
   0x3e, 0x00, 0x00, 0x00, 0xc0, 0x07, 0xf0, 0x7f, 0x78, 0x7c, 0xf8, 0x78,
   0x7c, 0x1e, 0x0f, 0x3e, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xc0, 0x3f, 0x78,
   0x7c, 0xf0, 0x79, 0x7c, 0x1f, 0x1f, 0x3e, 0xff, 0xff, 0xff, 0xff, 0x0f,
   0x00, 0x07, 0x7c, 0x7c, 0xc0, 0x78, 0x7c, 0x0f, 0x1f, 0x3e, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
   0x18, 0x60, 0xf0, 0x03, 0x18, 0xf0, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0x7f, 0xf8, 0xe1, 0x1f, 0x7e, 0xf8, 0x78, 0x3c, 0x00,
   0x00, 0x07, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xfc, 0xf3, 0x3f, 0xff, 0xfc,
   0x78, 0x3c, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00, 0x70, 0xe6, 0x9c, 0x73,
   0x38, 0xe7, 0x1c, 0x38, 0x1c, 0x00, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x70,
   0x67, 0x9c, 0x63, 0x70, 0xe7, 0xfc, 0x3c, 0x1e, 0x00, 0xc0, 0x03, 0x00,
   0x00, 0x00, 0x70, 0xee, 0xbc, 0x73, 0x70, 0xe7, 0xfc, 0x38, 0x1c, 0x00,
   0xe0, 0x01, 0x00, 0x00, 0x00, 0x70, 0xe7, 0xbc, 0x63, 0x30, 0xe7, 0xfc,
   0x70, 0x38, 0x00, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x70, 0xe6, 0xbc, 0x73,
   0x38, 0xe7, 0x1c, 0x70, 0x38, 0x00, 0xf8, 0xff, 0xff, 0xff, 0xff, 0x71,
   0x67, 0x9c, 0x63, 0x3f, 0xe7, 0xfc, 0x7c, 0x3e, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0xff, 0x71, 0xee, 0x9c, 0x73, 0x1f, 0xe7, 0xf8, 0x3c, 0x1e, 0x00,
   0xf8, 0xff, 0xff, 0xff, 0xff, 0x71, 0xe7, 0x9c, 0x63, 0x03, 0xe7, 0xf0,
   0x0c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

// soundtrack
Song song = {
  0, 
  150, 
  "eeeeeeegcde fffffeeeeddedg", 
  { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0} 
};

// constants
const byte step = 4;
const byte bitmapSize = 8;
const byte oneDamage = 10;
const byte gameWidth = 96;
const byte gameHeight = 64;

// player
byte playerHealth = 100;
byte playerX = 48;
byte playerY = 56;

// bullet
byte bulletX;
int bulletY;

// x, y, size, type, velocity
int trashes[][5] = {
  { 10, 0, 2, 1, 1 },
  { 50, 0, 1, 1, 2 }
};
const byte trashesCount = sizeof(trashes) / sizeof(trashes[0]);

// x, y, velocity, heal
int doctor[] = { 15, -50, 2, 20};

/*
 0 - menu,
 1 - single player
 2 - score
 */ 
byte stage = 0;

ScoreTable<GID_GALAXY_MADNESS> scoreTable;

void setup()
{
  initGame(INIT_ALL);
}

void loop()
{
  // main menu
  if (stage == 0) {
    // play music in menu
    sound.playSong(song);

    // should we start?
    if (buttonPressed(START_BUTTON)) {
      stage = 1;
    }
  }
  
  if (stage == 1) {
    gameLoop();
  } else if (stage == 2) {
	  scoreTable.update();
  }

  //draw everything
  pictureLoop();
}
