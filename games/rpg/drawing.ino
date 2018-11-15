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
  } while ( u8g2.nextPage() );

  // rebuild the picture after some delay
  delay(10);
}

void drawMenu()
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //logo
  u8g2.setCursor(15, 15);
  u8g2.print("DIY Handheld Game");
  
  //text
  u8g2.setCursor(20, 55);
  u8g2.print("press the start");
}

void drawWin()
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //win
  u8g2.setCursor(20, 15);
  u8g2.print("!! YOU WIN !!");
}

void drawLose()
{
  //rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  //lose
  u8g2.setCursor(20, 15);
  u8g2.print(" :( GAME OVER :(");
}

void drawSidebar()
{
  // rectangles
  u8g2.drawFrame(96, 0, 32, 64);
  
  // score
  u8g2.setCursor(100, 10);
  u8g2.print(String(playerCoins) + " / " + String(coinsQuantity));

  // health
  u8g2.drawFrame(100, 36, 24, 4);
  u8g2.drawBox(100, 36, playerHealth / 4.16, 4);
  
  // minimap
  u8g2.drawFrame(100, 44, 24, 16);
  u8g2.drawPixel(100 + mapX * SCREEN_COLS + playerX, 44 + mapY * SCREEN_ROWS + playerY);
}

void drawMap()
{ 
  // player - always centered
  u8g2.drawXBM(playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE, playerBits[random(2)]);

  // map
  for (int y = 0; y < SCREEN_ROWS; y++){
    for (int x = 0; x < SCREEN_COLS; x++){
      if (currentMap[y][x] == 2) {
        u8g2.drawXBM(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, wallBits);
      }
    }
  }

  // coins
  for (int i = 0; i < coinsQuantity; i++) {
    if (coins[i][0] == mapY && coins[i][1] == mapX) {
      u8g2.drawXBM(coins[i][3] * TILE_SIZE, coins[i][2] * TILE_SIZE, TILE_SIZE, TILE_SIZE, coinBits);
    }
  }

  // enemies
  for (int i = 0; i < enemiesQuantity; i++) {
    if (enemies[i][0] == mapY && enemies[i][1] == mapX) {
      u8g2.drawXBM(enemies[i][3] * TILE_SIZE, enemies[i][2] * TILE_SIZE, TILE_SIZE, TILE_SIZE, enemyBits[random(2)]);
    }
  }

  // doctors
  for (int i = 0; i < doctorsQuantity; i++) {
    if (doctors[i][0] == mapY && doctors[i][1] == mapX) {
      u8g2.drawXBM(doctors[i][3] * TILE_SIZE, doctors[i][2] * TILE_SIZE, TILE_SIZE, TILE_SIZE, doctorBits);
    }
  }
}

void drawFight()
{
  // rectangle
  u8g2.drawFrame(0, 0, 128, 64);

  // win
  u8g2.setCursor(20, 10);
  u8g2.print("THIS IS FIGHT!!!");
  u8g2.drawHLine(0, 14, 128);

  // draw player 4-60
  u8g2.setCursor(4, 24);
  u8g2.print("YOU");

  u8g2.drawFrame(4, 28, 50, 4);
  u8g2.drawBox(4, 28, playerHealth / 1.92, 4);

  u8g2.setCursor(4, 40);
  u8g2.print("health " + (String)playerHealth);

  u8g2.setCursor(4, 48);
  u8g2.print("attack " + (String)playerAttack);

  u8g2.drawXBM(4, 53, TILE_SIZE, TILE_SIZE, playerBits[random(2)]);

  // draw enemy 66-124
  u8g2.setCursor(66, 24);
  u8g2.print("ENEMY");

  u8g2.drawFrame(66, 28, 50, 4);
  u8g2.drawBox(66, 28, enemies[currentEnemy][4] / 1.92, 4);

  u8g2.setCursor(66, 40);
  u8g2.print("health " + (String)enemies[currentEnemy][4]);

  u8g2.setCursor(66, 48);
  u8g2.print("attack " + (String)enemies[currentEnemy][5]);

  u8g2.drawXBM(66, 53, TILE_SIZE, TILE_SIZE, enemyBits[random(2)]);

  // draw bullet whos on the move
  u8g2.drawDisc(whoseMove ? 52 : 116, 21, 2, U8G2_DRAW_ALL);

  // draw last wound
  if (lastAttack > 0) {
    u8g2.setCursor(whoseMove ? 41 : 105, 60);
    u8g2.print("-" + (String)lastAttack);
  }
}
