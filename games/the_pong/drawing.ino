void pictureLoop()
{
  display.firstPage();
  do {
    // decide what to draw at this iteration
    switch (stage) {
      case 0:
        drawMenu();
        break;
      case 1:
        drawMatch();
        break;
      case 2:
        drawLose();
        break;
      case 3:
        drawWin();
        break;
      default:
        break;
    }
  } while (display.nextPage());

  // rebuild the picture after some delay
  //delay(10);
}

void drawWin()
{
  drawBar();
  display.drawBigText(28, 35, "YOU WIN");
}

void drawLose()
{
  drawBar();
  display.drawBigText(26, 35, "GAME OVER");
}

void drawMenu()
{
  display.drawBigText(28, 25, "THE PONG");
  display.drawSmallText(28, 55, "press the start");
}

void drawBar()
{
  // logo
  display.drawSmallText(45, 10, "THE PONG");
  
  // rectangle
  display.drawFrame(0, 0, 128, 64);

  // score
  if (stage > 0) {
    display.drawSmallText(4, 10, String(aiScore));
    display.drawSmallText(DISPLAY_WIDTH - 8, 10, String(playerScore));
  }
}

void drawMatch()
{
  drawBar();

  // v line 
  //display.drawVLine(64, 4, 56);

  // paddles
  display.setContrast(128);
  display.drawBox(0, aiY, paddleWidth, paddleHeight);
  display.drawBox(DISPLAY_WIDTH - paddleWidth, playerY, paddleWidth, paddleHeight);

  // ball 
  display.drawPixel(ballX, ballY);
}
