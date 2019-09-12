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
struct Game 
{
    public:
        byte width = 128;
        byte height = 64;
        byte sidebarWidth = 32;
        bool step = true;

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

        void draw()
        {
            display.drawVLine(96, 0, height);
            display.drawSmallText(98, 6, "SCORE");
            display.drawSmallText(98, 14, (String)scoreTable.getScore());
        }
} game;

class Player 
{
    public:     
        byte getX()
        {
            return x;
        }  

        byte getY()
        {
            return y;
        }       

        byte getWidth()
        {
            return width;
        }

        byte getHeight()
        {
            return height;
        }

        void draw()
        {
            // health
            display.drawSmallText(98, 26, "HEALTH");
            display.drawFrame(98, 32, 28, 4);
            display.drawBox(98, 32, health / 3.57, 4);

            // player
            if (y > 0 || y < game.height - height) {
                display.drawXBM(x, y, width, height, playerBits);    
            }
        }

        void hurt(byte howMuch)
        {
            if (health > howMuch) {
                health -= howMuch;
                sound.playTone(100);
            } else {
                game.stage = 2;
                sound.playTone(100, 300);
            }
        }

        void checkMovement()
        {
            if (buttonPressed(ACTION_BUTTON)) {
                // jump
                y -= 5;
                sound.playTone(200);
            } else {
                // fall down
                y += 3;
            }
        }

        void loop()
        {
            game.step = !game.step;

            // collision - floor and ceiling
            if (y < 0 || y > game.height - height) {
                hurt(2);
            } else if (game.step % 2 == 0) {
                scoreTable.addScore(1);
            }
        }

    private:
        byte width = 8;
        byte height = 8;

        byte x = 10;
        int y = 0;

        byte health = 100;

} player;

class Pipe 
{
    public:
        void setX(int newX)
        {
            x = newX;
        }

        void draw()
        {
            if (x > 0 && x < game.width - game.sidebarWidth) {
                // up part
                display.drawBox(x, 0, width, y - space / 2);
                // down part
                display.drawBox(x, y + space / 2, width, game.height);
            }
        } 

        void move()
        {
            if (game.step % 2 == 0) {
                x -= 3;
            }

            if (x - width < 0) {
                x = random(game.width, game.width * 1.5);
                y = random(space, game.height - space);
                // over time, space get smaller
                space = random(space / 1.2, space);
            }
        }

        void checkCollisionWithPlayer()
        {
            if (
                (
                    player.getX() < x + width && player.getX() + player.getWidth() > x &&
                    player.getY() < y - space / 2 && player.getY() + player.getHeight() > 0
                )
                ||
                (
                    player.getX() < x + width && player.getX() + player.getWidth() > x &&
                    player.getY() < game.height && player.getY() + player.getHeight() > y + space / 2
                )
            ) {
                // up part
                display.drawBox(x, 0, width, y - space / 2);
                // down part
                display.drawBox(x, y + space / 2, width, game.height);
                player.hurt(3);
            }
        }

    private: 
        int x = game.width;
        int y = game.height / 2;
        byte width = 5;
        byte space = 44;
};

class PipeCollection
{
    public:
        static const byte pipesCount = 5;
        Pipe pipes[pipesCount];

        PipeCollection()
        {
            for (int i = 0; i < pipesCount; i++) {
                pipes[i].setX(i * 35);
            }
        }

        void draw()
        {
            for (int i = 0; i < pipesCount; i++) {
                pipes[i].draw();
            }
        }

        void move()
        {
            for (int i = 0; i < pipesCount; i++) {
                pipes[i].move();
                pipes[i].checkCollisionWithPlayer();
            }
        }
} pipeCollection;


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
        player.loop();
        pipeCollection.move();  
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
                game.draw();
                player.draw();
                pipeCollection.draw();
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
