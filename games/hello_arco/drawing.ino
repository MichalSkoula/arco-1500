void drawMenu()
{
    display.drawBigText(8, 16, "HELLO ARCO");
    display.drawSmallText(8, 26, "press the start");
}

void drawGame()
{
    display.drawSmallText(8, 16, "SCORE " + (String)scoreTable.getScore());
    display.drawSmallText(8, 26, "press the action button will you win");
}
