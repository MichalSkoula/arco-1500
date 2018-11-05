void movement()
{
  // keypad movement
  char key = keypad.getKey();
  if (key == '1') {
    playerYnew = playerY - 1;
    playerXnew = playerX;
  } else if (key == '2') {
    playerYnew = playerY + 1;
    playerXnew = playerX;
  } else if (key == '3') {
    playerXnew = playerX - 1;
    playerYnew = playerY;
  } else if (key == '4') {
    playerXnew = playerX + 1;
    playerYnew = playerY;
  }
  
  // key not pressed
  if (!strlen(key)) {
    return;
  }
    
  // on the edge => change map?
  bool changeMap = false;
  if (playerYnew == SCREEN_ROWS) {
    mapY++;
    playerYnew = 0;
    changeMap = true;
  } else if (playerYnew == -1) {
    mapY--;
    playerYnew = SCREEN_ROWS - 1;
    changeMap = true;
  } else if (playerXnew == SCREEN_COLS) {
    mapX++;
    playerXnew = 0;
    changeMap = true;
  } else if (playerXnew == -1) {
    mapX--;
    playerXnew = SCREEN_COLS - 1;
    changeMap = true;
  }
  
  if (changeMap) {
    loadMap(mapY, mapX);
  }
  
  // can walk
  if (currentMap[playerYnew][playerXnew] != 1) {
    return;
  }

  // step sound
  playTone(500);

  // yes he can
  playerX = playerXnew;
  playerY = playerYnew;

  // pick coin
  for (int i = 0; i < coinsQuantity; i++) {
    if (coins[i][0] == mapY && coins[i][1] == mapX && coins[i][2] == playerY && coins[i][3] == playerX) {
      playerCoins++;
      coins[i][1] = 99; //haha put it away i dont know ho to unset item from array
    }
  }

  // pick doctor
  for (int i = 0; i < doctorsQuantity; i++) {
    if (doctors[i][0] == mapY && doctors[i][1] == mapX && doctors[i][2] == playerY && doctors[i][3] == playerX) {
      playerHealth += doctors[i][4];
      if (playerHealth > 100) {
        playerHealth = 100;
      }
      doctors[i][1] = 99; //haha put it away i dont know ho to unset item from array
    }
  }

  // enemy nearby ? maybe enter fight
  for (int i = 0; i < enemiesQuantity; i++) {
    if (enemies[i][0] == mapY && enemies[i][1] == mapX) { //in this map
      if (abs(enemies[i][2] - playerY) < 2 && abs(enemies[i][3] - playerX) < 2) {
        startFight(i);
      }
    }
  }
}
