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
  u8g2.print("!! YOU WON !!");
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
  //u8g2.setCursor(100, 4);
  //u8g2.print("coins");
  u8g2.setCursor(100, 10);
  u8g2.print(String(playerCoins) + " / " + String(coinsQuantity));

  // health
  //u8g2.setCursor(100, 28);
  //u8g2.print("health");
  u8g2.drawFrame(100, 36, 24, 4);
  u8g2.drawBox(100, 36, playerHealth / 4.16, 4);
  
  // minimap
  u8g2.drawFrame(100, 44, 24, 16);
  u8g2.drawPixel(100 + mapX * SCREEN_COLS + playerX, 44 + mapY * SCREEN_ROWS + playerY);
}

void drawMap()
{ 
  // player - always centered
  u8g2.drawXBM(playerX * TILE_SIZE, playerY * TILE_SIZE, TILE_SIZE, TILE_SIZE, playerBits);

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
}
