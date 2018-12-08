#include <gamelib.h>

const byte CELL_SIZE = 2;     // in pixels
const byte X = 64;            // number of columns of cells
const byte Y = 32;            // number of rows of cells
static_assert(X * CELL_SIZE <= DISPLAY_WIDTH && Y * CELL_SIZE <= DISPLAY_HEIGHT, "Size of display is 128x64 pixels");
static_assert((X * Y) % 8 == 0, "Disgusting cell count");

// 1 byte stores state of 8 cells
byte cells[(X * Y) / 8];
byte tmpCells[(X * Y) / 8];
bool pause = false;

/* functions ------------------------------------------------------------------ */
byte cell(byte x, byte y)
{
  int pos = y * X + x;
  return cells[pos / 8] & (1 << pos % 8);
}

void cell_set(byte x, byte y, bool alive)
{
  int pos = y * X + x;
  cells[pos / 8] = (cells[pos / 8] & ~(1 << (pos % 8))) | (alive << pos % 8);
}

void cell_set_tmp(byte x, byte y, bool alive)
{
  int pos = y * X + x;
  tmpCells[pos / 8] = (tmpCells[pos / 8] & ~(1 << (pos % 8))) | (alive << pos % 8);
}

//void resetCells(byte density)
void resetCells()
{
  for (int y = 0; y < Y; ++y)
    for (int x = 0; x < X; ++x)
      cell_set(x, y, random(100) < 50);
}

bool isAlive(byte x, byte y)
{
  if (x >= X || y >= Y)
    return false;
  return cell(x, y);
}

byte countNeighbourCells(byte x, byte y)
{
  byte count = 0;
  for (byte i = y == 0 ? 0 : y - 1; i < y + 2; ++i) {
    for (byte j = x == 0 ? 0 : x - 1; j < x + 2; ++j) {
        if (x == j && y == i)
          continue;
        if (isAlive(j, i))
          ++count;
    }
  }
  return count;
}

void updateCells()
{
  // alive cell must have 2 or 3 neighbours, otherwise it dies
  // dead cell with exactly 3 neighbours becomes alive  
  for (int y = 0; y < Y; ++y) {
    for (int x = 0; x < X; ++x) {
      int count = countNeighbourCells(x, y);
      if (cell(x, y)) {
        cell_set_tmp(x, y, count == 3 || count == 2);
      } else {
        cell_set_tmp(x, y, count == 3);
      }
    }
  }

  // copy state
  memcpy(cells, tmpCells, sizeof(cells));
  //for (int i = 0; i < sizeof(cells); ++i)
    //cells[i] = tmpCells[i];
}

void drawCells()
{
  for (int y = 0; y < Y; ++y) {
    for (int x = 0; x < X; ++x) {
      if (cell(x, y))
        display.drawBox(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    }
  }
}

/* start ------------------------------------------------------------------- */
void setup(void)
{
  initGame(BUTTONS);
  
  resetCells();
}

/* loop -------------------------------------------------------------------- */
void loop(void) {
  // restart game
  if (buttonPressed(START_BUTTON)) {
    resetCells();
  }
  // (un)pause game
  // TODO pressed action button -> 1 step?
  if (buttonPressed(ACTION_BUTTON))
    pause = !pause;

  // update state if unpaused
  if (!pause)
    updateCells();

  // draw state
  display.firstPage();
  do {
    drawCells();
  } while (display.nextPage());
  delay(10);
}
