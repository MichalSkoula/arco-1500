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
        scoreTable.draw();
        break;
      default:
        break;
    }
  } while (display.nextPage());

  // rebuild the picture after some delay
  delay(35);
}

void drawMenu()
{
  display.drawXBM(8, 1, 111, 34, logoBits);
  display.drawSmallText(25, 55, "press the start");
}

void drawGame()
{
  display.drawVLine(gameWidth, 0, gameHeight);

  // score
  display.drawSmallText(98, 10, "Score");         // set small font
  display.drawText(98, 20, (String)scoreTable.getScore());

  // health
  display.drawText(98, 35, "Health");
  display.drawFrame(98, 41, 30, 4);
  display.drawBox(98, 41, playerHealth / 3.33, 4);

  // player 
  display.drawXBM(playerX, playerY, bitmapSize, bitmapSize, playerBits);

  // doctor 
  display.drawXBM(doctor[0], doctor[1], bitmapSize, bitmapSize, doctorBits);

  // bullet
  if (bulletY >= 0) {
    display.drawPixel(bulletX, bulletY);
    display.drawPixel(bulletX, bulletY + 1);
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
