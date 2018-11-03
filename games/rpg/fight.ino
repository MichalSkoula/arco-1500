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
    actionButtonState = digitalRead(actionButton);
    if (actionButtonState == HIGH) {
      whoseMove = !whoseMove;
      byte attack = playerAttack + random(-2, 4);

      // attack
      if (enemies[currentEnemy][4] > attack) {
        enemies[currentEnemy][4] -= attack;
      } else {
        // enemy dead
        enemies[currentEnemy][1] = 99; //haha put it away i dont know ho to unset item from array
        stage = 1;
      }
    } 
  } else {
    // enemy move
    if (random(0, 10) == 1) {
      whoseMove = !whoseMove;
      byte attack = enemies[currentEnemy][5] + random(-2, 4);

      // attack 
      if (playerHealth > attack) {
        playerHealth -= attack;
      } else {
        // player dead 
        stage = 9;
      }
    }
  }
}
