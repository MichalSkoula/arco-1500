#include <U8g2lib.h>

// Display which does not send AC
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

// buttons, pins
const byte startButton = 13;
const byte actionButton = 12;
byte lastActionState = 0;

enum CellState
{
  Dead = 0,
  Alive,
  Born,
  Surviving  
};

const byte CELL_SIZE = 2;     // in pixels
const byte ROWS = 16;
const byte COLS = 32;
static_assert(ROWS * CELL_SIZE <= 64 && COLS * CELL_SIZE <= 128, "Size of display is 128x64 pixels");

byte cells[COLS][ROWS];
bool pause = false;

/* functions ------------------------------------------------------------------ */
//void resetCells(byte density)
void resetCells()
{
  for (int i = 0; i < COLS; ++i)
    for (int j = 0; j < ROWS; ++j)
      //cells[i][j] = random(100) < density ? CellState::Alive : CellState::Dead;
      cells[i][j] = random(100) < 50 ? CellState::Alive : CellState::Dead;
      //cells[i][j] = random(2) ? CellState::Alive : CellState::Dead;
}

bool isAlive(byte x, byte y)
{
  if (x >= COLS || y >= ROWS)
    return false;
  return cells[x][y] == CellState::Alive || cells[x][y] == CellState::Surviving;
}

byte countNeighbourCells(byte x, byte y)
{
  byte count = 0;
  for (byte i = x == 0 ? 0 : x - 1; i < x + 2; ++i) {
    for (byte j = y == 0 ? 0 : y - 1; j < y + 2; ++j) {
        if (x == i && y == j)
          continue;
        if (isAlive(i, j))
          ++count;
    }
  }
  return count;
}

void updateCells()
{
  // NOW                                  NEXT GEN
  // Dead:  not exactly 3 neighbours   -> Dead
  // Dead:  exactly 3 neighbours       -> Born
  // Alive: fewer than 2 more than 3   -> Dead
  // Alive: exactly 2 or 3 neighbours  -> Surviving
  //
  // cells surviving on to the next generation:
  //      Born || Surviving -> Alive
  //      Dead || Alive -> Dead
  // cells counted as neighbors:
  //      Alive || Surviving  
  for (int i = 0; i < COLS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      int count = countNeighbourCells(i, j);
      if (cells[i][j] == CellState::Alive) {
          if (count == 3 || count == 2) cells[i][j] = CellState::Surviving;
      } else {
          if (count == 3) cells[i][j] = CellState::Born;
      }
    }
  }
  for (int i = 0; i < COLS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      cells[i][j] = (cells[i][j] == CellState::Born || cells[i][j] == CellState::Surviving)
        ? CellState::Alive
        : CellState::Dead;
    }
  }
}

void drawCells()
{
  for (int i = 0; i < COLS; ++i) {
    for (int j = 0; j < ROWS; ++j) {
      if (cells[i][j] == CellState::Alive)
        u8g2.drawBox(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE);
    }
  }
}

/* start ------------------------------------------------------------------- */
void setup(void)
{
  pinMode(startButton, INPUT);
  pinMode(actionButton, INPUT);

  u8g2.begin();
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  resetCells();
}

/* loop -------------------------------------------------------------------- */
void loop(void) {
  // restart game
  if (digitalRead(startButton) == HIGH) {
    resetCells();
  }
  // (un)pause game
  // TODO pressed action button -> 1 step?
  byte actionState = digitalRead(actionButton);
  if (actionState != lastActionState && actionState == HIGH) {
    pause = !pause;
  }
  lastActionState = actionState;

  // update state if unpaused
  if (!pause)
    updateCells();

  // draw state
  u8g2.firstPage();
  do {
    drawCells();
  } while (u8g2.nextPage());
  delay(10);
}
