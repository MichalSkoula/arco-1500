#ifndef NOT_EMULATOR_U8G2_H
#define NOT_EMULATOR_U8G2_H

#include "Arduino.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern const Uint8 *pressedKeys;

extern const uint8_t *u8g2_font_5x7_tf;
extern const uint8_t *u8g2_font_9x15_tf;

#ifndef RESOLUTION_MULTIPLIER
    #define RESOLUTION_MULTIPLIER 5
#endif

constexpr int DISPLAY_W = 128;
constexpr int DISPLAY_H = 64;
constexpr int RENDER_SCALE = RESOLUTION_MULTIPLIER;
constexpr int WINDOW_W = DISPLAY_W * RENDER_SCALE;
constexpr int WINDOW_H = DISPLAY_H * RENDER_SCALE;

template<typename T>
inline constexpr T scale(T coord) {
    return coord * RENDER_SCALE;
}

#ifndef WINDOW_TITLE
	#define WINDOW_TITLE "not_emulator"
#endif

// TODO better fonts
#ifndef FONT_BIG_PATH
    #define FONT_BIG_PATH "/usr/share/fonts/dejavu/DejaVuSansMono.ttf"
#endif
#ifndef FONT_SMALL_PATH
    #define FONT_SMALL_PATH "/usr/share/fonts/dejavu/DejaVuSansMono.ttf"
#endif

enum CircleFill
{
	U8G2_DRAW_UPPER_RIGHT 	= 0x01,
	U8G2_DRAW_UPPER_LEFT 	= 0x02,
	U8G2_DRAW_LOWER_LEFT 	= 0x04,
	U8G2_DRAW_LOWER_RIGHT 	= 0x08,
	U8G2_DRAW_ALL = U8G2_DRAW_UPPER_RIGHT|U8G2_DRAW_UPPER_LEFT|U8G2_DRAW_LOWER_RIGHT|U8G2_DRAW_LOWER_LEFT
};

// TODO move SDL stuff to main.cpp?
class DisplayBase
{
public:
    DisplayBase();
    ~DisplayBase();

	// dummy function
	void begin() {}

	void setBitmapMode(int)
	{
		// TODO impl
	}

	void setContrast(int)
	{
		// TODO impl
	}

    void firstPage();
    bool nextPage();

    void drawPixel(int x, int y);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawHLine(int x, int y, int w);
    void drawVLine(int x, int y, int h);
    void drawFrame(int x, int y, int w, int h);
    void drawBox(int x, int y, int w, int h);
    void drawDisc(int x, int y, int r, uint8_t opt = U8G2_DRAW_ALL);

    void drawXBM(int x, int y, int w, int h, const uint8_t *data);

    void setFont(const uint8_t *font);
    void print(const String &text);
    void setCursor(int x, int y);

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool fullscreen = false;

	TTF_Font *smallFont;
	TTF_Font *bigFont;
	TTF_Font *font;
	SDL_Rect printCursor;
};


// dummy enum for constructor
enum { U8G2_R0 };

class U8G2_SSD1306_128X64_NONAME_1_HW_I2C : public DisplayBase
{
public:
	U8G2_SSD1306_128X64_NONAME_1_HW_I2C(int) {}
};

#endif	/* NOT_EMULATOR_U8G2_H */
