#include <gamelib.h>

// we want score tracking!
// GID_HELLO - unique identifier - must fill in arduino/portable/sketchbook/libraries/gamelib/score.h:8
ScoreTable<GID_HELLO> scoreTable;

// stage of the game
// 0        menu
// 1        game
// 2        score table
byte stage = 0;


/* start ------------------------------------------------------------------- */
void setup(void)
{
    initGame(BUTTONS);
}

/* loop -------------------------------------------------------------------- */
void loop(void) 
{
    // which stage we are? And what should we do?
    if (stage == 0) {
        // menu - wait for start button
        if (buttonPressed(START_BUTTON)) {
            stage = 1;
        }
    } else if (stage == 1) {
        // game
        playGame();
    } else if (stage == 2) {
        // game over => show score table
        scoreTable.update();
    }

    // draw everything
    display.firstPage();
    do {
        // decide what to draw at this iteration
        switch (stage) {
            case 0:
                drawMenu();
                break;
            case 1:
                drawGame();
                break;
            case 2:
                scoreTable.draw();
                break;
            default:
                break;
        }
    } while (display.nextPage());

    // rebuild the picture after some delay
    delay(30);
}
