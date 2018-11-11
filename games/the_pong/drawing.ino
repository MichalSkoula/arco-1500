void pictureLoop()
{
  u8g2.firstPage();
  do {
    //decide what to draw at this iteration
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
  } while ( u8g2.nextPage() );

  // rebuild the picture after some delay
  //delay(10);
}

void drawWin()
{
  drawBar();

  u8g2.setFont(u8g2_font_9x15_tf );
  u8g2.setCursor(28, 35);
  u8g2.print("YOU WIN");
}

void drawLose()
{
  drawBar();

  u8g2.setFont(u8g2_font_9x15_tf );
  u8g2.setCursor(26, 35);
  u8g2.print("GAME OVER");
}

void drawMenu()
{
  u8g2.setFont(u8g2_font_9x15_tf );
  u8g2.setCursor(28, 25);
  u8g2.print("THE PONG");

  u8g2.setFont(u8g2_font_5x7_tf);
  u8g2.setCursor(28, 55);
  u8g2.print("press the start");
}

void drawBar()
{
  // logo
  u8g2.setFont(u8g2_font_5x7_tf);
  u8g2.setCursor(45, 10);
  u8g2.print("THE PONG");

  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  // score
  if (stage > 0) {
    u8g2.setCursor(5, 10);
    u8g2.print((String)aiScore); 

    u8g2.setCursor(screenWidth - 5, 10);
    u8g2.print((String)playerScore); 
  }
}

void drawMatch()
{
  drawBar();

  // v line 
  //u8g2.drawVLine(64, 4, 56);

  // paddles
  u8g2.setContrast(128);
  u8g2.drawBox(0, aiY, paddleWidth, paddleHeight);
  u8g2.drawBox(screenWidth - paddleWidth, playerY, paddleWidth, paddleHeight);

  // ball 
  u8g2.drawPixel(ballX, ballY);
}
