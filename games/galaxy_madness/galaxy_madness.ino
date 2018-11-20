#include <U8g2lib.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// button pins
const byte startButton = 13;
byte startButtonState = 0;

const byte actionButton = 12;
byte actionButtonState = 0;

const byte buzzerPin = 11;

// d-pad
const byte leftButton = 2;
const byte rightButton = 4; 

// bitmaps
static unsigned char playerBits[] = { 0x18, 0x3c, 0x7e, 0x7e, 0x3c, 0x3c, 0x7e, 0xff };
static unsigned char trashSmallBits[2][8] = { 
  { 0x30, 0x3c, 0xfe, 0xfe, 0x7f, 0x3f, 0x7e, 0x30 },
  { 0x10, 0x3c, 0x7e, 0x7e, 0x7f, 0x3f, 0x7c, 0x36 }
};

static unsigned char trashBigBits[2][32] = {
  {
    0x30, 0x3e, 0xfc, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xff, 0x3f, 0xff, 0x3f,
    0xfe, 0x3f, 0xf8, 0x1f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x1f, 0xfe, 0x3f,
    0xfe, 0x3f, 0xf8, 0x1f, 0xe0, 0x10, 0x00, 0x00
  },
  {
    0x00, 0x38, 0x70, 0x7e, 0xf8, 0x7f, 0xfe, 0x7f, 0xff, 0x3f, 0xfe, 0x3f,
    0xfe, 0x3f, 0xf8, 0x1f, 0xfc, 0x3f, 0xf0, 0x3f, 0xf0, 0x1f, 0xf8, 0x3f,
    0xfe, 0x7f, 0xf8, 0x7e, 0xe0, 0x10, 0x00, 0x00
  } 
};

// constants
const byte step = 4;
const byte bitmapSize = 8;
const byte oneDamage = 25;
const byte gameWidth = 96;
const byte gameHeight = 64;

// variables
byte playerScore = 0;
byte playerHealth = 100;
byte playerX = 48;
byte playerY = 56;

byte bulletX;
int bulletY;

// x, y, size, type, velocity
int trashes[][5] = {
  { 10, 0, 2, 1, 1 },
  { 50, 0, 1, 1, 2 }
};
const byte trashesCount = sizeof(trashes) / sizeof(trashes[0]);

/*
 0 - menu,
 1 - single player
 2 - lose
 */ 
byte stage = 0;

void setup()
{
  // activate buttons
  pinMode(startButton, INPUT);
  pinMode(actionButton, INPUT);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);

  // buzzer
  pinMode(buzzerPin, OUTPUT);

  // u82
  u8g2.begin();
  u8g2.setBitmapMode(1); //bitmap transparent background

  // serial
  Serial.begin(9600);

  // random seed
  randomSeed(analogRead(0));
}

void loop() 
{
  // main menu
  if (stage == 0) {
    startButtonState = digitalRead(startButton);
    if (startButtonState == HIGH) {
      stage = 1;
    }
  }
  
  if (stage == 1) {
    gameLoop();
  }  

  //draw everything
  pictureLoop();
}
