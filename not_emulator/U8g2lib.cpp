#include "U8g2lib.h"

const Uint8 *pressedKeys = nullptr;

const uint8_t *u8g2_font_5x7_tf = reinterpret_cast<const uint8_t *>(1);
const uint8_t *u8g2_font_9x15_tf = reinterpret_cast<const uint8_t *>(2);

// TODO move SDL stuff to main.cpp?

DisplayBase::DisplayBase()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow(WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_W, WINDOW_H, 0
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    // small font's height is approximately 6 px (4.5 pt)
    smallFont = TTF_OpenFont(FONT_SMALL_PATH, static_cast<int>(round(scale(4.5))));
    if (!smallFont) {
        printf("Failed to open small font: %s", TTF_GetError());
        exit(1);
    }
    // big font's height is approximately 10 px (7.5 pt)
    bigFont = TTF_OpenFont(FONT_BIG_PATH, static_cast<int>(round(scale(7.5))));
    if (!bigFont) {
        printf("Failed to open big font: %s", TTF_GetError());
        exit(1);
    }
    font = smallFont;
    printCursor = { 0, 0, 0, 0 };

    transparentTextures = false;
}

DisplayBase::~DisplayBase()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(smallFont);
    TTF_CloseFont(bigFont);
    TTF_Quit();
    SDL_Quit();
}

void DisplayBase::setBitmapMode(int transparent) {
    transparentTextures = transparent;
}

void DisplayBase::firstPage()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            exit(0);
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    exit(0);

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

bool DisplayBase::nextPage() {
    SDL_RenderPresent(renderer);
    delay(50);		// TODO remove - limit frame rate but input should be responsive
    return false;
}

void DisplayBase::drawPixel(int x, int y)
{
    drawBox(x, y, 1, 1);
}

void DisplayBase::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, scale(x1), scale(y1), scale(x2), scale(y2));
}

void DisplayBase::drawHLine(int x, int y, int w)
{
    SDL_RenderDrawLine(renderer, scale(x), scale(y), scale(x) + scale(w), scale(y));
}

void DisplayBase::drawVLine(int x, int y, int h)
{
    SDL_RenderDrawLine(renderer, scale(x), scale(y), scale(x), scale(y) + scale(h));
}

void DisplayBase::drawFrame(int x, int y, int w, int h)
{
    SDL_Rect r{scale(x), scale(y), scale(w), scale(h)};
    SDL_RenderDrawRect(renderer, &r);
}

void DisplayBase::drawBox(int x, int y, int w, int h)
{
    SDL_Rect r{scale(x), scale(y), scale(w), scale(h)};
    SDL_RenderFillRect(renderer, &r);
}

void DisplayBase::drawDisc(int x, int y, int r, uint8_t opt)
{
    UNUSED(opt);
    // TODO impl
    // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
    // OR
    // SDL_gfx OR U8g2
    drawBox(x - r , y - r, r * 2, r * 2);
}

void DisplayBase::drawXBM(int x, int y, int w, int h, const uint8_t *data)
{
    // TODO cache textures
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetRenderTarget(renderer, texture);
    if (transparentTextures) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    int rw = static_cast<int>(ceil(w / 8.0) * 8);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (data[(i * rw) / 8 + j / 8] & (1 << (j % 8)))
                SDL_RenderDrawPoint(renderer, j, i);
        }
    }
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_Rect rect{scale(x), scale(y), scale(w), scale(h)};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

void DisplayBase::setFont(const uint8_t *font)
{
    this->font = font == u8g2_font_5x7_tf ? smallFont : bigFont;
}

void DisplayBase::print(const String &text)
{
    SDL_Color fg = { 255, 255, 255, 255 };
    //SDL_Color bg = { 0, 0, 0 };
    //SDL_Surface *surface = TTF_RenderText_Solid(font, text, fg);
    //SDL_Surface *surface = TTF_RenderText_Shaded(font, text, fg, bg);
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, fg);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &(printCursor.w), &(printCursor.h));
    printCursor.y -= printCursor.h;		// setCursor sets position of bottom left corner
    // TODO adjust x by width - original U8g2lib font has different width
    SDL_RenderCopy(renderer, texture, nullptr, &printCursor);
    // TODO probably inaccurate, but print is never called directly - always with setCursor()
    printCursor.x += printCursor.w;
    // TODO cache rendered text
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void DisplayBase::setCursor(int x, int y)
{
    printCursor.x = scale(x);
    printCursor.y = scale(y);
}
