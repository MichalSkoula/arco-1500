#ifndef GAMELIB_SCORE_H
#define GAMELIB_SCORE_H

#include <EEPROM.h>
#include "display.h"
#include "input.h"

enum GameId {
	GID_RPG = 0,
	GID_THE_PONG,
	GID_GAME_OF_LIFE,
	GID_GALAXY_MADNESS,
	GID_SNAKE
};

// TODO move from gamelib.h to different file and remove this forward declaration
void softReset();

using score_t = uint16_t;

struct Score
{
	// 3 characters A-Z (26 letters, 5 bits each, 1 bit unused)
    unsigned int c1 : 5, c2 : 5, c3 : 5, : 1;
	score_t value;
};

static_assert(sizeof(Score) == 4, "Score struct size should be 4 bytes");

// ScoreTable
// Usage:
// define global variable ScoreTable<gameId> scoreTable
// when game ends call scoreTable.gameOver(finalScore)
// and in loop call scoreTable.update() and scoreTable.draw()
//
// TODO Inner state size
//
// Format:
// Saved to EEPROM (max 512 bytes of memory)
// TODO checksum, probably not CRC? table too big? or CRC without table? too slow?
//		this? https://en.wikipedia.org/wiki/Fletcher%27s_checksum#Fletcher-16
// TODO problem with CRC/Checksum byte - it will be the most used cell
// Format
// Header (1 B) 		GameId
// N Records (N * 4 B)  Name + Score
// 		Name (2 B)		3 characters A-Z
//		Score (2 B)		uint
// CRC (1 B)			TODO

template<int gameId>
class ScoreTable
{
public:
    // Score count
    static constexpr uint8_t Count = 5;

    // ScoreTable size in EEPROM
    static constexpr uint8_t Size = 1 + Count * sizeof(Score) + 1;

	ScoreTable()
	{
		init();
	}

	score_t getScore() const
	{
		return score.value;
	}

	void setScore(score_t value)
	{
		score.value = value;
	}

	void addScore(int value)
	{
		// TODO detect negative/positive overflow
		score.value += value;
	}

	void update()
	{
		if (stage == 0 && buttonPressed(START_BUTTON)) {
			stage = isHighScore() ? 1 : 2;
		} else if (stage == 1) {
			if (buttonPressed(LEFT_BUTTON) && nameIndex > 0) {
				--nameIndex;
			} else if (buttonPressed(RIGHT_BUTTON) && nameIndex < 2) {
				++nameIndex;
			} else if (buttonDown(DOWN_BUTTON)) {
				switch (nameIndex) {
					case 0: if (score.c1 > 0) --score.c1; break;
					case 1: if (score.c2 > 0) --score.c2; break;
					case 2: if (score.c3 > 0) --score.c3; break;
				}
			} else if (buttonDown(UP_BUTTON)) {
				switch (nameIndex) {
					case 0: if (score.c1 < 'Z' - 'A') ++score.c1; break;
					case 1: if (score.c2 < 'Z' - 'A') ++score.c2; break;
					case 2: if (score.c3 < 'Z' - 'A') ++score.c3; break;
				}
			} else if (buttonPressed(START_BUTTON)) {
				byte i = findLowestScore();
				EEPROM.put(gameId * Size + 1 + i * sizeof(Score), score);
				score.value = 0;
				stage = 2;
			}
		} else if (stage == 2 && buttonPressed(START_BUTTON)) {
            softReset();
		}
	}

	void draw()
	{
		if (stage == 0) {
			drawGameOver();
		} else if (stage == 1) {
			drawNameInput();
		} else if (stage == 2) {
			drawTable();
		}
	}

private:
	// TODO smaller inner state
	//		stage, nameIndex and isHighScore flag in one byte
	// 0		Game Over/New High Score Screen		// TODO different stages?
	// 1		Name Input Screen
	// 2		High Score Table
	byte stage = 0;
	byte nameIndex = 0;
	Score score;

    // TODO better - currently ScoreTable is at offset gameId * Size
	void init()
	{
		score = { 0, 0, 0, 0 };
		byte id;
		if (EEPROM.get(gameId * Size, id) != gameId) {
			EEPROM.put(gameId * Size, gameId);
			for (byte i = 0; i < Count; ++i) {
				EEPROM.put(gameId * Size + 1 + i * sizeof(Score), score);
			}
			// TODO crc
		}
	}

	byte findLowestScore()
	{
        score_t low = static_cast<score_t>(-1);     // max score_t value
		score_t s;
		byte lowIndex = Count;
		for (byte i = 0; i < Count; ++i) {
			EEPROM.get(gameId * Size + 1 + i * sizeof(Score) + 2, s);
			if (s < low) {
				low = s;
				lowIndex = i;
			}
		}
		return lowIndex;
	}

	// TODO cache? it's just one bit (+ 1 bit for dirty cache? or determine by stage?)
	// 		or cache index of the lowest score?
	bool isHighScore()
	{
		byte i = findLowestScore();
        if (i < Count) {
            score_t low;
            EEPROM.get(gameId * Size + 1 + i * sizeof(Score) + 2, low);
            return score.value > low;
        }
        return false;
	}

	void drawGameOver()
	{
		if (isHighScore()) {
			display.drawBigText(15, 10, "GAME OVER");
			// TODO
			display.drawSmallText(15, 35, "New High Score: " + (String)score.value);
		} else {
			display.drawBigText(15, 10, "GAME OVER");
			display.drawSmallText(15, 35, "Score: " + (String)score.value);
		}
	}

	void drawNameInput()
	{
		display.drawBigText(15, 10, "YOUR NICK");

		display.drawBigText(20 + 0 * 20, 40, (String)static_cast<char>(score.c1 + 'A'));
		display.drawBigText(20 + 1 * 20, 40, (String)static_cast<char>(score.c2 + 'A'));
		display.drawBigText(20 + 2 * 20, 40, (String)static_cast<char>(score.c3 + 'A'));
		for (byte i = 0; i < 3; ++i) {
			if (i == nameIndex) {
				display.drawFrame(18 + i * 20, 26, 13, 20);
			} else {
				display.drawBigText(20 + i * 20, 46, "_");
			}
		}
	}

	// TODO probably not necessary to render this too often
	void drawTable()
	{
		display.drawBigText(15, 10, "HIGH SCORES");
		display.drawSmallText(15, 18, "--------------------");

		// TODO could probably be optimized to use less memory
		// read scores from memory
		Score scores[Count];
		for (byte i = 0; i < Count; ++i) {
			EEPROM.get(gameId * Size + 1 + i * sizeof(Score), scores[i]);
		}

		// sort them
		for (byte i = 0; i < Count; ++i) {
			score_t high = scores[i].value;
			byte index = i;
			for (byte j = i; j < Count; ++j) {
				if (scores[j].value > high) {
					high = scores[j].value;
					index = j;
				}
			}
			if (index != i) {
				Score tmp = scores[index];
				scores[index] = scores[i];
				scores[i] = tmp;
			}
		}

		// draw them
		for (byte i = 0; i < Count; ++i) {
			char name[4];
			name[0] = scores[i].c1 + 'A';
			name[1] = scores[i].c2 + 'A';
			name[2] = scores[i].c3 + 'A';
			name[3] = 0;
			display.drawSmallText(15, 25 + i * 9, name);
	  		display.drawText(85, 25 + i * 9, (String)scores[i].value);
		}
	}
};

#endif	/* GAMELIB_SCORE_H */
