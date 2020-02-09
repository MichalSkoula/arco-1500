#include <gamelib.h>

// we want score tracking!
// GID_HELLO - unique identifier - must fill in arduino/portable/sketchbook/libraries/gamelib/score.h:8
ScoreTable<GID_TANK> scoreTable;

static unsigned char tankBits[][6] = {
    { 0x0c, 0x2d, 0x1e, 0x3f, 0x1e, 0x21 }, 
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
        display.drawBigText(8, 16, F("TANK 92"));
        display.drawSmallText(8, 26, F("press the start"));
    }

    void drawBorder()
    {
        display.drawVLine(0, 0, height + 10);
        display.drawVLine(width, 0, height + 10);
        display.drawHLine(1, height, width);

        display.drawText(3, height + 9, F("LIVES"));
        display.drawText(width / 2, height + 9, F("SCORE"));
    }

    bool isThisCollision(int x1, int y1, byte width1, byte height1, bool active1, int x2, int y2, byte width2, byte height2, bool active2) {
		if (x1 >= x2 + width2 || x1 + width1 <= x2 || y1 >= y2 + height2 || y1 + height1 <= y2 || !active1 || !active2) {
		   	return false;
		} 
		return true;
	}
} game;

class Bullet {
public:
    int x = 5;
    int y = 5;
    byte width = 2;
    byte height = 2;
    byte direction = 0; // clockwise from up = 0
    byte step = 5;
    bool active = false;

    void draw() 
    {
        if (active) {
            display.drawBox(x, y, width, height);
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
    int x = 49;
    int y = 44;
    byte width = 6;
    byte height = 6;
    byte step = 2;
    byte lives = 3;
    byte direction = 0;
    Bullet bullet;

    void draw()
    {
        display.drawXBM(x, y, width, height, tankBits[direction]);

        for (byte i; i < lives; i++) {
        	display.drawXBM(20 + i * (width + 2), game.height + 3, width, height, tankBits[0]);
        }
        display.drawText(92, game.height + 9, (String)scoreTable.getScore());

        bullet.draw();
    }

    void hurt()
    {
    	lives--;
    	x = 49;
    	y = 46;

    	sound.playTone(100, 20);

        if (lives == 0) {
            game.stage = 2;
        }
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

    void shoot()
    {
        if (buttonPressed(ACTION_BUTTON)) {
            bullet.shoot(direction, x + width / 2 - 1, y + height / 2 - 1);
        }

        bullet.move();
    }
private:
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
} player;

class Enemy {
public:
    int x = 5;
    int y = 5;
    byte width = 6;
    byte height = 6;
    byte step = 2;
    byte direction = 0;
    Bullet bullet;

    void draw()
    {
        display.drawXBM(x, y, width, height, tankBits[direction]);
        bullet.draw();
    }

    void shoot()
    {
    	if (random(20) == 0) {
    		bullet.shoot(direction, x + width / 2, y + height / 2);
    	}
    	bullet.move();
    }

    void move()
    {
    	if (random(10) == 0) {
    		direction = random(0, 4);
    	}

		if (direction == 3 && x - step >= 0) {
            x -= step;
        } else if (direction == 1 && x + width + step < game.width) {
            x += step;
        } else if (direction == 0  && y - step >= 0) {
            y -= step;
        } else if (direction == 2 && y + height + step < game.height) {
            y += step;
        }
    }

    void is_shot()
    {
        if (game.isThisCollision(player.bullet.x, player.bullet.y, player.bullet.width, player.bullet.height, player.bullet.active, x, y, width, height, true)) {
            x = 5;
            y = 5;
            player.bullet.active = false;
            sound.playTone(200, 5);
            scoreTable.addScore(1);
        }
    }

    void is_player_shot()
    {
        if (game.isThisCollision(player.x, player.y, player.width, player.height, true, bullet.x, bullet.y, bullet.width, bullet.height, bullet.active)) {
            bullet.active = false;
            player.hurt();
        }
    }
};

class EnemyCollection {
public:
    static const byte enemiesCount = 4;
    Enemy enemies[enemiesCount];

    void draw()
    {
        for (byte i = 0; i < enemiesCount; i++) {
            enemies[i].draw();
        }
    }

    void doAllThings()
    {
        for (byte i = 0; i < enemiesCount; i++) {
            enemies[i].move();
            enemies[i].shoot();
            enemies[i].is_shot();
            enemies[i].is_player_shot();
        }
    }
} enemyCollection;


/* functions -------------------------------------------------------------- */
void playGame() {
    player.move();
    player.shoot();

    enemyCollection.doAllThings();
}

void drawGame() {
    game.drawBorder();

    player.draw();

    enemyCollection.draw();
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
