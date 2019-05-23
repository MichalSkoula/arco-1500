#include <gamelib.h>

// 0        menu
// 1        game
// 2        score table
byte stage = 0;

// grid lines
byte lines[] = { 0, 16 };
const byte linesCount = sizeof(lines) / sizeof(lines[0]);

// bitmaps
static unsigned char playerBits[] = { 0x1e, 0x1e, 0x0c, 0x3f, 0x0c, 0x1e, 0x12, 0x3f };

struct Player {
    byte x = 60;
    byte y = 54;
    byte width = 6;
    byte height = 8;
    byte step = 6;
    byte health = 100;
};
Player player;

struct Game {
    byte gridWidth = 128;
    byte gridHeight = 32;
};
Game game;


ScoreTable<GID_SURFER> scoreTable;

/* functions ------------------------------------------------------------------ */

void gameLoop()
{
    // keypad movement
    if (buttonDown(LEFT_BUTTON) && player.x - player.step >= 0) {
        player.x -= player.step;
        sound.playTone(100);
    } else if (buttonDown(RIGHT_BUTTON) && player.x + player.width + player.step < game.gridWidth) {
        player.x += player.step;
        sound.playTone(100);
    } else if (buttonDown(UP_BUTTON) && player.y - player.step > game.gridHeight) {
        player.y -= player.step;
        sound.playTone(100);
    } else if (buttonDown(DOWN_BUTTON) && player.y + player.height + player.step < game.gridHeight * 2) {
        player.y += player.step;
        sound.playTone(100);
    } 

    // move grid lines 
    for (int x = 0; x < linesCount; x++) {
        lines[x] += 2;
        if (lines[x] > game.gridHeight) {
            lines[x] = 0;
        }
    } 
}


/* start ------------------------------------------------------------------- */
void setup(void)
{
    initGame(BUTTONS);
}

/* loop -------------------------------------------------------------------- */
void loop(void) 
{

    // main menu
    if (stage == 0) {
        // should we start?
        if (buttonPressed(START_BUTTON)) {
            stage = 1;
        }
    }
  
    if (stage == 1) {
        gameLoop();
    } else if (stage == 2) {
        scoreTable.update();
    }

    //draw everything
    pictureLoop();
}
