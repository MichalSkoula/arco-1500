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
        drawGame();
        break;
      case 2:
        drawLose();
        break;
      default:
        break;
    }
  } while (display.nextPage());

  // rebuild the picture after some delay
  delay(10);
}

void drawMenu()
{
  display.drawBigText(1, 15, "Galaxy Madness");
  display.drawSmallText(25, 55, "press the start");
}

void drawLose()
{
  display.drawSmallText(20, 15, "GAME OVER");     // set small font
  display.drawText(20, 35, "SCORE: " + (String)playerScore);
}

void drawGame()
{
  display.drawVLine(gameWidth, 0, gameHeight);

  // score
  display.drawSmallText(98, 10, "Score");         // set small font
  display.drawText(98, 20, (String)playerScore);

  // health
  display.drawText(98, 35, "Health");
  display.drawFrame(98, 41, 30, 4);
  display.drawBox(98, 41, playerHealth / 3.33, 4);

  // player 
  display.drawXBM(playerX, playerY, bitmapSize, bitmapSize, playerBits);

  // bullet
  if (bulletY >= 0) {
    display.drawPixel(bulletX, bulletY);
  }

  // trashes
  for (byte i = 0; i < trashesCount; i++) {
    display.drawXBM(
      trashes[i][0],
      trashes[i][1], 
      bitmapSize * trashes[i][2],
      bitmapSize * trashes[i][2],
      trashes[i][2] == 1 ? trashSmallBits[trashes[i][3]] : trashBigBits[trashes[i][3]]
    );
  }
}
