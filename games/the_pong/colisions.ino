void checkHittingWall() 
{
  if (ballX > DISPLAY_WIDTH - 1) {
    ballReset(false);
    aiScore++;
    sound.playTone(500, 20);
  } else if (ballX < 0) {
    ballReset(true);
    playerScore++;
    sound.playTone(500, 20);
  }
}

void checkHittingCeiling()
{
  if (ballY > DISPLAY_HEIGHT - 1 || ballY < 0) {
    ballYVel = -ballYVel;
    sound.playTone(100);
  }
}

void checkPaddleHit() 
{
  if (ballX > DISPLAY_WIDTH - paddleWidth && ballY >= playerY && ballY <= (playerY + paddleHeight) && ballXVel == 1) {
    // right (player);
    ballXVel = -ballXVel;
    sound.playTone(100);
  } else if (ballX < 0 + paddleWidth && ballY >= aiY && ballY <= (aiY + paddleHeight) && ballXVel == -1) {
    // left (ai)
    ballXVel = -ballXVel;
    sound.playTone(100);
  }
}

void ballReset(bool left)
{
  //If left is true, then ball should launch from the left, otherwise launch from the right
  //Ball should launch at a random Y location and at a random Y velocity

  ballY = random(DISPLAY_HEIGHT);
  if (random(2) > 0) {
    ballYVel = 1;
  } else {
    ballYVel = -1;
  }

  if (left) {
    ballXVel = 1;
    ballX = DISPLAY_WIDTH / 2; 
  } else {
    ballXVel = -1;
    ballX = DISPLAY_WIDTH / 2; 
  }
}
