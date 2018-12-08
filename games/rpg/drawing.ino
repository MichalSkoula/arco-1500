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
        drawMap();
        drawSidebar();
        break;
      case 2:
        drawFight();
        break;
      case 8:
        drawWin();
        break;
      case 9:
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
  // rectangle
  display.drawFrame(0, 0, 128, 64);

  // logo
  display.drawText(15, 15, "DIY Handheld Game");
  
  // text
  display.drawText(20, 55, "press the start");
}

void drawWin()
{
  // rectangle
  display.drawFrame(0, 0, 128, 64);

  // win
  display.drawText(20, 15, "!! YOU WIN !!");
}

void drawLose()
{
  // rectangle
  display.drawFrame(0, 0, 128, 64);

  // lose
  display.drawText(20, 15, " :( GAME OVER :(");
}

void drawSidebar()
{
  // rectangles
  display.drawFrame(96, 0, 32, 64);
  
  // score
  display.drawText(100, 10, String(playerCoins) + " / " + String(coinsQuantity));

  // health
  display.drawFrame(100, 36, 24, 4);
  display.drawBox(100, 36, playerHealth / 4.16, 4);
  
  // minimap
  display.drawFrame(100, 44, 24, 16);
  display.drawPixel(100 + mapX * SCREEN_COLS + playerX, 44 + mapY * SCREEN_ROWS + playerY);
}

void drawMap()
{ 
  // player - always centered
  display.drawXBM(playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE, playerBits[random(2)]);

  // map
  for (int y = 0; y < SCREEN_ROWS; y++){
    for (int x = 0; x < SCREEN_COLS; x++){
      if (currentMap[y][x] == 2) {
        display.drawXBM(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, wallBits);
      }
    }
  }

  // coins
  for (int i = 0; i < coinsQuantity; i++) {
    if (coins[i][0] == mapY && coins[i][1] == mapX) {
      display.drawXBM(coins[i][3] * TILE_SIZE, coins[i][2] * TILE_SIZE, TILE_SIZE, TILE_SIZE, coinBits);
    }
  }

  // enemies
  for (int i = 0; i < enemiesQuantity; i++) {
    if (enemies[i][0] == mapY && enemies[i][1] == mapX) {
      display.drawXBM(enemies[i][3] * TILE_SIZE, enemies[i][2] * TILE_SIZE, TILE_SIZE, TILE_SIZE, enemyBits[random(2)]);
    }
  }

  // doctors
  for (int i = 0; i < doctorsQuantity; i++) {
    if (doctors[i][0] == mapY && doctors[i][1] == mapX) {
      display.drawXBM(doctors[i][3] * TILE_SIZE, doctors[i][2] * TILE_SIZE, TILE_SIZE, TILE_SIZE, doctorBits);
    }
  }
}

void drawFight()
{
  // rectangle
  display.drawFrame(0, 0, 128, 64);

  // win
  display.drawText(20, 10, "THIS IS FIGHT!!!");
  display.drawHLine(0, 14, 128);

  // draw player 4-60
  display.drawText(4, 24, "YOU");

  display.drawFrame(4, 28, 50, 4);
  display.drawBox(4, 28, playerHealth / 1.92, 4);

  display.drawText(4, 40, "health " + (String)playerHealth);
  display.drawText(4, 48, "attack " + (String)playerAttack);

  display.drawXBM(4, 53, TILE_SIZE, TILE_SIZE, playerBits[random(2)]);

  // draw enemy 66-124
  display.drawText(66, 24, "ENEMY");

  display.drawFrame(66, 28, 50, 4);
  display.drawBox(66, 28, enemies[currentEnemy][4] / 1.92, 4);

  display.drawText(66, 40, "health " + (String)enemies[currentEnemy][4]);
  display.drawText(66, 48, "attack " + (String)enemies[currentEnemy][5]);

  display.drawXBM(66, 53, TILE_SIZE, TILE_SIZE, enemyBits[random(2)]);

  // draw bullet whos on the move
  display.drawDisc(whoseMove ? 52 : 116, 21, 2, U8G2_DRAW_ALL);

  // draw last wound
  if (lastAttack > 0) {
    display.drawText(whoseMove ? 41 : 105, 60, "-" + (String)lastAttack);
  }
}
