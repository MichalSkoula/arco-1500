void checkHittingWall() 
{
  if (ballX > screenWidth - 1) {
    ballReset(false);
    aiScore++;
    playTimedTone(500, 20);
  } else if (ballX < 0) {
    ballReset(true);
    playerScore++;
    playTimedTone(500, 20);
  }
}

void checkHittingCeiling()
{
  if (ballY > screenHeight - 1 || ballY < 0) {
    ballYVel = -ballYVel;
    playTone(100);
  }
}

void checkPaddleHit() 
{
  if (ballX > screenWidth - paddleWidth && ballY >= playerY && ballY <= (playerY + paddleHeight) && ballXVel == 1) {
    // right (player);
    ballXVel = -ballXVel;
    playTone(100);
  } else if (ballX < 0 + paddleWidth && ballY >= aiY && ballY <= (aiY + paddleHeight) && ballXVel == -1) {
    // left (ai)
    ballXVel = -ballXVel;
    playTone(100);
  }
}

void ballReset(bool left)
{
  //If left is true, then ball should launch from the left, otherwise launch from the right
  //Ball should launch at a random Y location and at a random Y velocity

  ballY = random(screenHeight);
  if (random(2) > 0) {
    ballYVel = 1;
  } else {
    ballYVel = -1;
  }

  if (left) {
    ballXVel = 1;
    ballX = screenWidth / 2; 
  } else {
    ballXVel = -1;
    ballX = screenWidth / 2; 
  }
}
