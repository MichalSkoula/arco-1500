void gameLoop()
{
  // keypad movement
  if (buttonDown(LEFT_BUTTON) && playerX - step >= 0) {
    playerX -= step;
  } else if (buttonDown(RIGHT_BUTTON) && playerX + step < gameWidth) {
    playerX += step;
  }

  // action buttons - firing
  if (buttonDown(ACTION_BUTTON) && bulletY <= 0) {
    bulletX = playerX + bitmapSize / 2;
    bulletY = gameHeight - bitmapSize;
    playTone(400);
  }

  // bullet exists?
  if (bulletY >= 0) {
    bulletY -= 6;
  }

  // trash movement
  for (byte i = 0; i < trashesCount; i++) {

    // move down
    trashes[i][1] += trashes[i][4];

    // collision with bullet
    if (
      trashes[i][0] < bulletX &&
      trashes[i][0] + bitmapSize * trashes[i][2] > bulletX &&
      trashes[i][1] < bulletY &&
      trashes[i][1] + bitmapSize * trashes[i][2] > bulletY &&
      bulletY >= 0 //only bullets on screen :)
    ) {
      playTone(200, 50);

      // destroy bullet
      bulletY = -1;

      if (trashes[i][2] == 2) {
        // decrease size of trash?
        trashes[i][2] = 1;
        trashes[i][0] += bitmapSize / 2; //center
        playerScore++;
      } else {
        // destroy trash
        trashes[i][1] = 90;
        playerScore++;
      }

      // speed it up
      trashes[i][4] += 1;
    }

    // collision with player
    if (
      trashes[i][0] < playerX + bitmapSize &&
      trashes[i][0] + bitmapSize * trashes[i][2] > playerX && 
      trashes[i][1] < playerY + bitmapSize && 
      trashes[i][1] + bitmapSize * trashes[i][2] > playerY 
    ) {
      playTone(100, 100);

      // destroy trash
      trashes[i][1] = 90;

      // decrease player health
      byte damage = trashes[i][2] * oneDamage;
      if (playerHealth - damage > 0) {
        playerHealth -= damage;
      } else {
        // die 
        stage = 2;
      }
    }

    // out of screen
    if (trashes[i][1] > gameHeight) {
      trashes[i][3] = random(0, 2); // random type - bitmap
      trashes[i][2] = random(1, 3); // random size
      trashes[i][1] = random(-40, -10); //y
      trashes[i][0] = random(0, gameWidth - bitmapSize * trashes[i][2]); //x
    }
  }
}
