#include <gamelib.h>

// constants
const byte winningScore = 10;
const byte paddleHeight = 16;
const byte paddleWidth = 4;

// variables
byte playerScore = 0;
byte aiScore = 0;

int playerY = 24;
int aiY = 24;

byte aiSpeed = 3;
byte playerSpeed = 2;

int ballX = DISPLAY_WIDTH / 2;
int ballY = DISPLAY_HEIGHT / 2;
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
  initGame(BUTTONS | JOYSTICK | SOUND);
}

void loop() 
{
  // main menu
  if (stage == 0) {
    if (buttonPressed(START_BUTTON)) {
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
    if (buttonPressed(UP_BUTTON) && playerY > 0) {
      playerY = playerY - playerSpeed;
    } else if (buttonPressed(DOWN_BUTTON) && playerY + paddleHeight < DISPLAY_HEIGHT) {
      playerY = playerY + playerSpeed;
    } 

    // ai movement
    if (aiY <= 0 || aiY + paddleHeight >= DISPLAY_HEIGHT) {
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
