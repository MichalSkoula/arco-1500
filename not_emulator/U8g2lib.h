#ifndef NOT_EMULATOR_U8G2_H
#define NOT_EMULATOR_U8G2_H

#include "Arduino.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern const Uint8 *pressedKeys;

extern const uint8_t *u8g2_font_5x7_tf;
extern const uint8_t *u8g2_font_9x15_tf;

constexpr int DISPLAY_W = 128;
constexpr int DISPLAY_H = 64;
constexpr int RENDER_SCALE = 3;
constexpr int WINDOW_W = DISPLAY_W * RENDER_SCALE;
constexpr int WINDOW_H = DISPLAY_H * RENDER_SCALE;

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

// TODO move SDL stuff to main.cpp
class DisplayBase
{
public:
	DisplayBase()
	{
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();

		//SDL_SetWindowTitle(window, title.c_str());
		window = SDL_CreateWindow(WINDOW_TITLE,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WINDOW_W, WINDOW_H, 0
		);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		// TODO scale coordinates and fonts "manually"? what about bitmaps?
		SDL_RenderSetScale(renderer, RENDER_SCALE, RENDER_SCALE);

		//SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");		// linear filtering

        smallFont = TTF_OpenFont(FONT_SMALL_PATH, 7);
        if (!smallFont) {
            printf("Failed to open small font: %s", TTF_GetError());
            exit(1);
        }
        bigFont = TTF_OpenFont(FONT_BIG_PATH, 15);
        if (!bigFont) {
            printf("Failed to open big font: %s", TTF_GetError());
            exit(1);
        }
		font = smallFont;
		printCursor = { 0, 0, 0, 0 };
	}

	~DisplayBase()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_CloseFont(smallFont);
		TTF_CloseFont(bigFont);
		TTF_Quit();
		SDL_Quit();
	}

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

	void firstPage()
	{
		SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
				exit(0);
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_ESCAPE:
						exit(0);
						break;
					case SDLK_f:
						fullscreen = !fullscreen;
						//SDL_WINDOW_FULLSCREEN
						//SDL_WINDOW_FULLSCREEN_DESKTOP
						SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
						// TODO for some reason, viewport is not centered in fullscreen (with or without the commented code)
						/*if (fullscreen) {
							int w, h;
							SDL_GetWindowSize(window, &w, &h);
							SDL_Rect viewport = { (w - WINDOW_W) / 2, (h - WINDOW_H) / 2, WINDOW_W, WINDOW_H };
							SDL_RenderSetViewport(renderer, &viewport);
						} else {
							SDL_RenderSetViewport(renderer, nullptr);
						}*/
						break;
				}
			}
        }

        pressedKeys = SDL_GetKeyboardState(nullptr);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);     	// black background
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);   // white everything else
	}

	bool nextPage() {
		SDL_RenderPresent(renderer);
		delay(50);		// TODO remove - limit frame rate but input should be responsive
		return false;
	}

	void drawPixel(int x, int y)
	{
		SDL_RenderDrawPoint(renderer, x, y);
	}
	
	void drawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	}

	void drawHLine(int x, int y, int w)
	{
		SDL_RenderDrawLine(renderer, x, y, x + w, y);
	}

	void drawVLine(int x, int y, int h)
	{
		SDL_RenderDrawLine(renderer, x, y, x, y + h);
	}

	void drawFrame(int x, int y, int w, int h)
	{
		SDL_Rect r{x, y, w, h};
		SDL_RenderDrawRect(renderer, &r);
	}

	void drawBox(int x, int y, int w, int h)
	{
		SDL_Rect r{x, y, w, h};
		SDL_RenderFillRect(renderer, &r);
	}

    void drawDisc(int x, int y, int r, uint8_t opt = U8G2_DRAW_ALL)
	{
        UNUSED(opt);
		// TODO impl
		// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
		// OR
		// SDL_gfx OR U8g2
		drawBox(x - r , y - r, r * 2, r * 2);
	}

	void drawXBM(int x, int y, int w, int h, const uint8_t *data)
	{
		// TODO cache textures
		SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetRenderTarget(renderer, texture);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (data[(i * w) / 8 + j / 8] & (1 << (j % 8)))
                    SDL_RenderDrawPoint(renderer, j, i);
			}
		}
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_Rect rect{x, y, w, h};
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}

	void setFont(const uint8_t *font)
	{
		this->font = font == u8g2_font_5x7_tf ? smallFont : bigFont;
	}

	void print(const String &text)
	{
        SDL_Color fg = { 255, 255, 255, 255 };
		//SDL_Color bg = { 0, 0, 0 };
		//SDL_Surface *surface = TTF_RenderText_Solid(font, text, fg);
		//SDL_Surface *surface = TTF_RenderText_Shaded(font, text, fg, bg);
		SDL_Surface *surface = TTF_RenderText_Blended(font, text, fg);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(texture, nullptr, nullptr, &(printCursor.w), &(printCursor.h));
		printCursor.y -= printCursor.h;		// setCursor sets position of bottom left corner
		SDL_RenderCopy(renderer, texture, nullptr, &printCursor);
		// TODO probably inaccurate, but print is never called directly - always with setCursor()
		printCursor.x += printCursor.w;
		// TODO cache rendered text
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}

	void setCursor(int x, int y)
	{
		printCursor.x = x;
		printCursor.y = y;
	}

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
