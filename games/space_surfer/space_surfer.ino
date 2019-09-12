#include <gamelib.h>

/* headers ------------------------------------------------------------------ */
boolean circleRect(float cx, float cy, float radius, float rx, float ry, float rw, float rh);

/* graphics ------------------------------------------------------------------ */
static unsigned char playerBits[] = { 0x1e, 0x1e, 0x0c, 0x3f, 0x0c, 0x1e, 0x12, 0x3f };

byte lines[] = { 0, 16 };
const byte linesCount = sizeof(lines) / sizeof(lines[0]);


/* classes ------------------------------------------------------------------ */
struct Game {
    byte gridWidth = 128;
    byte gridHeight = 32;

    byte gameWidth = 128;
    byte gameHeight = 64;

    byte speed = 2;

    // 0        menu
    // 1        game
    // 2        score table
    byte stage = 0;
} game;

class Player {
    public:
        byte x = 60;
        byte y = 54;
        byte width = 6;
        byte height = 8;
        byte step = 6;
        byte health = 100;

        void draw()
        {
            display.drawXBM(x, y, width, height, playerBits);
        }

        void hurt(byte strength)
        {
            if (health - strength < 0) {
                game.stage = 2;
            } else {
                health -= strength;
            }
            sound.playTone(100, 30);
        }

        void checkMovement()
        {
            if (buttonPressed(LEFT_BUTTON) && x - step >= 0) {
                moveHorizontal(-1);
            } else if (buttonPressed(RIGHT_BUTTON) && x + width + step < game.gridWidth) {
                moveHorizontal(1);
            } else if (buttonPressed(UP_BUTTON) && y - step > game.gridHeight) {
                moveVertical(-1);
            } else if (buttonPressed(DOWN_BUTTON) && y + height + step < game.gridHeight * 2) {
                moveVertical(1);
            } 
        }

        void moveHorizontal(int movement)
        {
            x += step * movement;
            sound.playTone(200);
        }

        void moveVertical(int movement)
        {
            y += step * movement;
            sound.playTone(200);
        }
} player;


class Enemy {
    public:
        byte x;
        byte y;
        byte sizeCoeff;
        byte strength;

        void die()
        {
            y = game.gridHeight - (game.gridHeight / sizeCoeff) * 2;
            x = random(4, 124);
        }

        void move()
        {
            y += game.speed;
        }

        void draw()
        {
            if (y > game.gridHeight - (y / sizeCoeff) * 2) {
                display.drawDisc(x, y, y / sizeCoeff);
            }
        }

        boolean checkCollision()
        {
            return circleRect(x, y, y / sizeCoeff, player.x, player.y, player.width, player.height);
        }
};
Enemy enemies[] = { 
    { 10, 0, 10, 40 },
    { 80, 10, 12, 35 },
    { 50, 0, 14, 30 },
    { 110, 20, 16, 25 },
};
const byte enemiesCount = sizeof(enemies) / sizeof(enemies[0]);

ScoreTable<GID_SURFER> scoreTable;


/* functions ------------------------------------------------------------------ */

void gameLoop()
{
    // player movement
    player.checkMovement();

    // move grid lines 
    for (int i = 0; i < linesCount; i++) {
        lines[i] += game.speed;
        if (lines[i] > game.gridHeight) {
            lines[i] = 0;
        }
    }

    // move enemies
    for (int i = 0; i < enemiesCount; i++) {
        enemies[i].move();
        
        if (enemies[i].y > game.gameHeight) {
            enemies[i].die();
        }
    }

    // collisions
    for (int i = 0; i < enemiesCount; i++) {
        if (enemies[i].checkCollision()) {
            enemies[i].die();
            player.hurt(enemies[i].strength);
        }
    }

    if (game.stage == 1) {
        scoreTable.addScore(1);
    } else if (game.stage == 2) {
        scoreTable.update();
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
    if (game.stage == 0) {
        // should we start?
        if (buttonPressed(START_BUTTON)) {
            game.stage = 1;
        }
    }
  
    // game or game over
    if (game.stage == 1) {
        gameLoop();
    } else if (game.stage == 2) {
        scoreTable.update();
    }

    // draw everything
    display.firstPage();
    do {
        // decide what to draw at this iteration
        switch (game.stage) {
            case 0:
                drawGrid();
                drawMenu();
                break;
            case 1:
                drawGrid();
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
