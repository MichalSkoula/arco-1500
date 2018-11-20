#include <U8g2lib.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// buttons, pins
const byte startButton = 13;
const byte actionButton = 12;
byte lastStartState = 0;
byte lastActionState = 0;

// 128x64 pixels
const byte PX_SIZE = 4;     // in pixels
const byte X = 32;          // max x/y coord
const byte Y = 16;

struct Point {
  signed char x;
  signed char y;
};

// 0 is head
Point snake[200];
int size;

Point speed;
Point directions[4] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
byte direction = 0;
bool changeDirection = false;

Point food;

bool pause = false;

/* functions ------------------------------------------------------------------ */

// TODO randomFreePoint
Point randomPoint()
{
  Point p;
  p.x = random(X);
  p.y = random(Y);
  return p;
}

void resetGame()
{
  speed = {0, 0};
  
  size = 3;  
  snake[0] = randomPoint();
  for (int i = 1; i < size; ++i)
    snake[i] = snake[0];
  
  food = randomPoint();
}

void drawSnake()
{
  for (int i = 0; i < size; ++i) {
    u8g2.drawBox(snake[i].x * PX_SIZE, snake[i].y * PX_SIZE, PX_SIZE, PX_SIZE);
  }
}

void drawFood()
{
  u8g2.drawBox(food.x * PX_SIZE, food.y * PX_SIZE, PX_SIZE, PX_SIZE);  
}

void updateSnake()
{
  // check collision with food
  if (food.x == snake[0].x && food.y == snake[0].y) {
    ++size;
    food = randomPoint();
  }

  // update parts of snek
  for (int i = size; i > 0; --i) {
    snake[i] = snake[i - 1];
  }

  // update snek's head
  snake[0].x += speed.x;
  snake[0].y += speed.y;

  // check collisions with its body
  // TODO show score and restart?
  if (speed.x != 0 || speed.y != 0) {
    int i;
    for (i = 1; i < size; ++i) {
      if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        break;
    }
    if (i < size)   // snek ate itself
      size = i;
  }

  // wrap around
  if (snake[0].x < 0)
    snake[0].x = X - 1;
  if (snake[0].x >= X)
    snake[0].x = 0;
  if (snake[0].y < 0)
    snake[0].y = Y - 1;
  if (snake[0].y >= Y)
    snake[0].y = 0;
}

/* start ------------------------------------------------------------------- */
void setup(void)
{
  pinMode(startButton, INPUT);
  pinMode(actionButton, INPUT);

  u8g2.begin();
  Serial.begin(9600);
  
  randomSeed(analogRead(0));

  resetGame();
}

/* loop -------------------------------------------------------------------- */
// TODO slower start, speed up as snek grows
void loop(void) {
  // TODO one button clock-wise and the other counter-clockwise?
  // change direction (counter-clockwise)
  byte state = digitalRead(startButton);
  if (state != lastStartState && state == HIGH) {
    direction++;
    if (direction >= 4)
      direction = 0;
    speed = directions[direction];
  }
  lastStartState = state;
  
  // (un)pause game
  state = digitalRead(actionButton);
  if (state != lastActionState && state == HIGH) {
    pause = !pause;
  }
  lastActionState = state;

  if (!pause)  
    updateSnake();

  // draw state
  u8g2.firstPage();
  do {
    drawSnake();
    drawFood();
  } while (u8g2.nextPage());
  
  delay(20);    // TODO get rid of delay
}
