#include <U8g2lib.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// button pins
const byte startButton = 13;
byte startButtonState = 0;

const byte buzzerPin = 11;

// d-pad
const byte upButton = 3;
const byte downButton = 6; 


// constants
const byte winningScore = 5;
const byte paddleHeight = 16;
const byte paddleWidth = 4;
const byte screenWidth = 128;
const byte screenHeight = 64;

// variables
byte playerScore = 0;
byte aiScore = 0;

int playerY = 24;
int aiY = 24;

byte aiSpeed = 3;
byte playerSpeed = 2;

int ballX = screenWidth / 2;
int ballY = screenHeight / 2;
int ballXVel = 1;
int ballYVel = 1;
byte ballSpeed = 2;

byte aiDirection = 0;

/*
 0 - menu,
 1 - single player
 2 - lose
 3 - win
 */ 
byte stage = 0;

void setup()
{
  // activate buttons
  pinMode(startButton, INPUT);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  // buzzer
  pinMode(buzzerPin, OUTPUT);

  // u82
  u8g2.begin();

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
      aiDirection = random(0, 2);
    }
  }
  
  if (stage == 1 && aiScore >= winningScore) {
    // he lost to AI
    stage = 2;
  } else if(stage == 1 && playerScore >= winningScore) {
    // he win
    stage = 3;
  } else if (stage == 1) {

    // player movement
    if (digitalRead(upButton) == LOW && playerY > 0) {
      playerY = playerY - playerSpeed;
    } else if (digitalRead(downButton) == LOW && playerY + paddleHeight < screenHeight) {
      playerY = playerY + playerSpeed;
    } 

    // ai movement
    if (aiY <= 0 || aiY + paddleHeight >= screenHeight) {
      aiDirection = !aiDirection;
    }
    if (aiDirection == 0) {
      aiY = aiY - aiSpeed;
    } else if(aiDirection == 1) {
      aiY = aiY + aiSpeed;
    }

    // collisions with ball
    checkPaddleHit();
    checkHittingWall();
    checkHittingCeiling();

    // Update ball position:
    ballX += ballXVel * ballSpeed;
    ballY += ballYVel * ballSpeed;
  }

  //draw everything
  pictureLoop();
}

