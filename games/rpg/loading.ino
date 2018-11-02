// load map from flash memory to ram
void loadMap(byte mapY, byte mapX)
{
  for (byte y = 0; y < SCREEN_ROWS; y++) {
    for (byte x = 0; x < SCREEN_COLS; x++) {
      currentMap[y][x] = pgm_read_byte(&(maps[mapY][mapX][y][x]));
    }
  }
}
