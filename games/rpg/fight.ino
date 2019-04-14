void startFight(byte enemyIndex)
{
  currentEnemy = enemyIndex;
  whoseMove = 1;
  stage = 2;
}

void fight()
{
  if (whoseMove == 1) {
    // player move
    if (buttonDown(ACTION_BUTTON)) {
      whoseMove = !whoseMove;
      sound.playTone(300);
      lastAttack = playerAttack + random(-2, 3);

      // attack
      if (enemies[currentEnemy][4] > lastAttack) {
        enemies[currentEnemy][4] -= lastAttack;
      } else {
        // enemy dead
        enemies[currentEnemy][1] = 99; //haha put it away i dont know ho to unset item from array
        stage = 1;
        lastAttack = 0;
      }
    } 
  } else {
    // enemy move
    if (random(0, 15) == 1) {
      whoseMove = !whoseMove;
      sound.playTone(300);
      lastAttack = enemies[currentEnemy][5] + random(-2, 3);

      // attack 
      if (playerHealth > lastAttack) {
        playerHealth -= lastAttack;
      } else {
        // player dead 
        stage = 9;
      }
    }
  }
}
