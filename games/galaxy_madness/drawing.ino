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
        drawGame();
        break;
      case 2:
        drawLose();
        break;
      default:
        break;
    }
  } while ( u8g2.nextPage() );

  // rebuild the picture after some delay
  delay(10);
}

void drawMenu()
{
  u8g2.setFont(u8g2_font_9x15_tf);

  //logo
  u8g2.setCursor(1, 15);
  u8g2.print("Galaxy Madness");
  
  u8g2.setFont(u8g2_font_5x7_tf);

  //text
  u8g2.setCursor(25, 55);
  u8g2.print("press the start");
}

void drawLose()
{
  u8g2.setFont(u8g2_font_5x7_tf);

  u8g2.setCursor(20, 15);
  u8g2.print("GAME OVER");

  u8g2.setCursor(20, 35);
  u8g2.print("SCORE: " + (String)playerScore);
}

void drawGame()
{
  u8g2.drawVLine(gameWidth, 0, gameHeight);

  u8g2.setFont(u8g2_font_5x7_tf);

  // score
  u8g2.setCursor(98, 10);
  u8g2.print("Score");
  u8g2.setCursor(98, 20);
  u8g2.print((String)playerScore);

  // health
  u8g2.setCursor(98, 35);
  u8g2.print("Health");
  u8g2.drawFrame(98, 41, 30, 4);
  u8g2.drawBox(98, 41, playerHealth / 3.33, 4);

  // player 
  u8g2.drawXBM(playerX, playerY, bitmapSize, bitmapSize, playerBits);

  // bullet
  if (bulletY >= 0) {
    u8g2.drawPixel(bulletX, bulletY);
  }

  // trashes
  for (byte i = 0; i < trashesCount; i++) {
    u8g2.drawXBM(
      trashes[i][0],
      trashes[i][1], 
      bitmapSize * trashes[i][2],
      bitmapSize * trashes[i][2],
      trashes[i][2] == 1 ? trashSmallBits[trashes[i][3]] : trashBigBits[trashes[i][3]]
    );
  }
}
