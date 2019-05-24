void drawGrid()
{
    // vertical lines - first are manual, because of negative coordinates fucks up the direction
    display.drawLine( 8, 32, 0, 36);
    display.drawLine(12, 32, 0, 39);
    display.drawLine(16, 32, 0, 43);
    display.drawLine(20, 32, 0, 47);
    display.drawLine(24, 32, 0, 52);
    display.drawLine(28, 32, 0, 58);
    display.drawLine(32, 32, 0, 64);

    for (int x = 0; x < 9; x++) {
        display.drawLine(64 - x * 4, 32, 64 - x * 8, 64);
    }
    for (int x = 0; x < 15; x++) {
        display.drawLine(64 + x * 4, 32, 64 + x * 8, 64);
    }

    // horizontal lines
    display.drawHLine(0, game.gridHeight, game.gridWidth);

    for (int x = 0; x < linesCount; x++) {
        display.drawHLine(0, 32 + lines[x], game.gridWidth);
    } 
}

void drawMenu()
{
    display.drawBigText(8, 16, "SPACE SURFER");
    display.drawSmallText(24, 26, "press the start");
}

void drawGame()
{
    display.drawSmallText(4, 8, "SCORE " + (String)scoreTable.getScore());

    display.drawSmallText(65, 8, "HEALTH");
    display.drawFrame(98, 2, 30, 6);
    display.drawBox(98, 2, player.health / 3.33, 6);

    for (int i = 0; i < enemiesCount; i++) {
        enemies[i].draw();
    }

    player.draw();
}

