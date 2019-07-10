void playGame() {
    // over 10? it is enought, game over :)
    if (scoreTable.getScore() > 10) {
        stage = 2;
    }

    // press button - add score
    if (buttonPressed(ACTION_BUTTON)) {
        scoreTable.addScore(1);
    }
}
