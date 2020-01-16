#include <gamelib.h>

// we want score tracking!
// GID_HELLO - unique identifier - must fill in arduino/portable/sketchbook/libraries/gamelib/score.h:8
ScoreTable<GID_TANK> scoreTable;

static unsigned char tankBits[][6] = {
    { 0x0c, 0x2d, 0x1e, 0x3f, 0x1e, 0x3f }, 
    { 0x15, 0x0e, 0x3e, 0x3e, 0x0e, 0x15 }, 
    { 0x21, 0x1e, 0x3f, 0x1e, 0x2d, 0x0c }, 
    { 0x2a, 0x1c, 0x1f, 0x1f, 0x1c, 0x2a }, 
};

/* classes ------------------------------------------------------------------ */
struct Game {
    public:
        byte width = 126;
        byte height = 54;

        // 0        menu
        // 1        game
        // 2        score table
        byte stage = 0;

        void drawMenu()
        {
            display.drawBigText(8, 16, "TANK 92");
            display.drawSmallText(8, 26, "press the start");
        }

        void drawBorder()
        {
            display.drawVLine(0, 0, height + 10);
            display.drawVLine(width, 0, height + 10);
            display.drawHLine(1, height, width);

            display.drawText(3, height + 9, "HEALTH");
            display.drawText(width / 2, height + 9, "SCORE");
        }
} game;

class Bullet {
    public:
        int x = 5;
        int y = 5;
        byte direction = 0; // clockwise from up = 0
        byte step = 5;
        bool friendly = true; // true - player, false - enemy
        bool active = false;

        Bullet() 
        {

        }

        void draw() 
        {
            if (active) {
                display.drawDisc(x, y, 1);
            }
        }

        void move() 
        {
            if (active) {
                switch (direction) {
                    case 0: y -= step; break;
                    case 1: x += step; break;
                    case 2: y += step; break;
                    case 3: x -= step; break;
                    default: break;
                }

                if (x < 0) {
                    active = false;
                } else if (x >= game.width) {
                    active = false;
                } else if (y < 0) {
                    active = false;
                } else if (y >= game.height) {
                    active = false;
                } 
            }
        }

        void shoot(byte dir, byte posX, byte posY)
        {
            if (!active) {
                active = true;
                direction = dir;
                x = posX;
                y = posY;
                sound.playTone(300, 5);
            }
        }
};

class Player {
    public:
        byte x = 49;
        byte y = 31;
        byte width = 6;
        byte height = 6;
        byte step = 2;
        byte health = 100;
        byte direction = 0;
        Bullet bullet;

        void draw()
        {
            display.drawXBM(x, y, width, height, tankBits[direction]);

            display.drawText(38, game.height + 9, (String)health);
            display.drawText(92, game.height + 9, (String)scoreTable.getScore());

            bullet.draw();
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

        void move()
        {
            if (buttonPressed(LEFT_BUTTON) && x - step >= 0) {
                moveHorizontal(-1);
                direction = 3;
            } else if (buttonPressed(RIGHT_BUTTON) && x + width + step < game.width) {
                moveHorizontal(1);
                direction = 1;
            } else if (buttonPressed(UP_BUTTON) && y - step >= 0) {
                moveVertical(-1);
                direction = 0;
            } else if (buttonPressed(DOWN_BUTTON) && y + height + step < game.height) {
                moveVertical(1);
                direction = 2;
            } 
        }

        void moveHorizontal(int movement)
        {
            x += step * movement;
            sound.playTone(200, 5);
        }

        void moveVertical(int movement)
        {
            y += step * movement;
            sound.playTone(200, 5);
        }

        void shoot()
        {
            if (buttonPressed(ACTION_BUTTON)) {
                bullet.shoot(direction, x + width / 2, y + height / 2);
            }

            bullet.move();
        }
} player;




/* functions -------------------------------------------------------------- */
void playGame() {
    // over 10? it is enought, game over :)
    if (scoreTable.getScore() > 10) {
        game.stage = 2;
        return;
    }

    player.move();
    player.shoot();
}

void drawGame() {
    game.drawBorder();

    player.draw();
}

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
        playGame();
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
    delay(20);
}
