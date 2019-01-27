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

  // doctor --------------------------------------------------------------------
  doctor[1] += doctor[2]; // move down
  // out of screen?
  if (doctor[1] > gameHeight) {
    doctor[1] = random(-100, -20); // y
    doctor[0] = random(0, gameWidth - bitmapSize);// x
    doctor[2] = random(2, 5); // velocity
  }
  // collision with player
  if (
    doctor[0] < playerX + bitmapSize &&
    doctor[0] + bitmapSize > playerX && 
    doctor[1] < playerY + bitmapSize && 
    doctor[1] + bitmapSize > playerY 
  ) {
    playTone(500, 100);

    // destroy doctor
    doctor[1] = random(-100, -20); // y
    doctor[0] = random(0, gameWidth - bitmapSize);// x
    doctor[2] = random(2, 5); // velocity

    // increase player health
    if (playerHealth + doctor[3] < 100) {
      playerHealth += doctor[3];
    } else {
      playerHealth = 100;
    }
  }

  // trash movement ------------------------------------------------------------
  for (byte i = 0; i < trashesCount; i++) {

    // move down
    trashes[i][1] += trashes[i][4];
    // move to the side? maybe
    if (random(3) == 1) {
      trashes[i][0] += random(-2, 3);  
    }

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

      // score - increase by size + velocity of the trash
      playerScore += trashes[i][2] + trashes[i][4];

      // destroy or cut the trash into half
      if (trashes[i][2] == 2) {
        // decrease size of trash?
        trashes[i][2] = 1;
        trashes[i][0] += bitmapSize / 2; //center
      } else {
        // destroy trash
        trashes[i][1] = 90;
      }

      // speed it up, maybe?
      if (random(3) == 1) {
        trashes[i][4] += 1;  
      }
      
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
      trashes[i][3] = random(0, 3); // random type - bitmap
      trashes[i][2] = random(1, 3); // random size
      trashes[i][1] = random(-40, -10); //y
      trashes[i][0] = random(0, gameWidth - bitmapSize * trashes[i][2]); //x
    }
  }
}
