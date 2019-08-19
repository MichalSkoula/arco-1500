#include <gamelib.h>

// score tracking
ScoreTable<GID_FLAPPY> scoreTable;

// graphics
static unsigned char playerBits[] = { 
    0xc3, 0xff, 0x81, 0xa5, 0x81, 0xdb, 0x7e, 0x3c };
static unsigned char playerBigBits[] = {
   0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0xfe, 0x7f, 0x02, 0x40, 0x32, 0x4c,
   0x32, 0x4c, 0x02, 0x40, 0xc2, 0x43, 0xe2, 0x47, 0x72, 0x4e, 0x32, 0x4c,
   0x06, 0x60, 0xfc, 0x3f, 0xf8, 0x1f, 0x00, 0x00 };

/* classes ------------------------------------------------------------------- */
struct Game {
    public:
        byte width = 128;
        byte height = 64;

        byte speed = 2;

        // 0 menu
        // 1 game
        // 2 score table
        byte stage = 0;

        void drawMenu()
        {
            display.drawBigText(8, 16, "Flappy Cat");
            display.drawSmallText(8, 36, "press the start");
            display.drawXBM(104, 4, 16, 16, playerBigBits);
        }

        void drawGame()
        {
            display.drawVLine(96, 0, height);
            display.drawSmallText(98, 6, "SCORE");
            display.drawSmallText(98, 14, (String)scoreTable.getScore());
        }
} game;

class Player {
    public:
        byte width = 8;
        byte height = 8;

        byte x = 10;
        int y = 0;

        byte health = 100;
                
        void draw()
        {
            // health
            display.drawSmallText(98, 26, "HEALTH");
            display.drawFrame(98, 32, 24, 4);
            display.drawBox(98, 32, health / 4.16, 4);

            // player
            if (y > 0 || y < game.height - height) {
                display.drawXBM(x, y, width, height, playerBits);    
            }
        }

        void die()
        {
            game.stage = 2;
            sound.playTone(100, 30);
        }

        void checkMovement()
        {
            if (buttonDown(ACTION_BUTTON)) {
                y -= 4;
                sound.playTone(200);
            } else {
                y += 2;
            }
        }

        void checkCollision()
        {
            // floor and ceiling
            if (y < 0 || y > game.height - height) {
                if (health > 0) {
                    health--;
                } else {
                    die();
                }
            }

            // blocks ...
        }
} player;


/* start ------------------------------------------------------------------- */
void setup(void)
{
    initGame(BUTTONS);
}

/* loop -------------------------------------------------------------------- */
void loop(void) 
{
    // which stage we are? And what should we do?
    if (game.stage == 0) {
        // menu - wait for start button
        if (buttonPressed(START_BUTTON)) {
            game.stage = 1;
        }
    } else if (game.stage == 1) {
        // game
        player.checkMovement();
        player.checkCollision();
    } else if (game.stage == 2) {
        // game over => show score table
        scoreTable.update();
    }

    // draw everything
    display.firstPage();
    do {
        // decide what to draw at this iteration
        switch (game.stage) {
            case 0:
                game.drawMenu();
                break;
            case 1:
                game.drawGame();
                player.draw();
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
