// Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "kissinger2.h"
#include "watchy.h"

// Screen dimension constants
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;

void *new_buffer() {
  return SDL_CreateRGBSurfaceWithFormat(0, 200, 200, 1, SDL_PIXELFORMAT_RGB888);
}

void buffer_clear(void *buffer, bool color) {
  SDL_Surface *surface = buffer;
  SDL_FillRect(
      surface, NULL,
      SDL_MapRGB(surface->format, color * 255, color * 255, color * 255));
}

void buffer_set_pixel(void *buffer, uint8_t x, uint8_t y, bool color) {
  if (x >= 200 || y >= 200) {
    return;
  }
  SDL_Surface *surface = buffer;
  uint8_t *pixels = (uint8_t *)surface->pixels;
  pixels[y * surface->pitch + x * surface->format->BytesPerPixel] = color * 255;
  pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 1] =
      color * 255;
  pixels[y * surface->pitch + x * surface->format->BytesPerPixel + 2] =
      color * 255;
}

void buffer_draw_rect(void *buffer, uint8_t x, uint8_t y, uint8_t w, uint8_t h,
                      bool color) {
  for (int i = x; i <= x + w; i++) {
    buffer_set_pixel(buffer, i, y, color);
    buffer_set_pixel(buffer, i, y + h, color);
  }
  for (int j = y; j <= y + h; j++) {
    buffer_set_pixel(buffer, x, j, color);
    buffer_set_pixel(buffer, x + w, j, color);
  }
}

void buffer_fill_rect(void *buffer, uint8_t x, uint8_t y, uint8_t w, uint8_t h,
                      bool color) {
  for (int i = x; i <= x + w; i++) {
    for (int j = y; j <= y + h; j++) {
      buffer_set_pixel(buffer, i, j, color);
    }
  }
}

void buffer_blit(void *buffer, uint8_t x, uint8_t y, uint8_t *bitmap, uint8_t w,
                 uint8_t h, bool color, uint8_t scale) {
  for (int j = y; j < y + h; j++) {
    for (int i = x; i < x + w; i++) {
      bool bit = (bitmap[((j - y) * w + (i - x)) / 8] &
                  (0b10000000 >> (((j - y) * w + (i - x)) % 8))) != 0;
      if (bit) {
        buffer_set_pixel(buffer, i, j, color);
      }
    }
  }
}

void buffer_print(void *buffer, uint8_t x, uint8_t y, char *text, bool color,
                  uint8_t scale) {
  size_t index = 0;
  size_t char_number = 0;
  while (text[index] != 0 && x + char_number * 17 < 200 && y < 200) {
    struct GlyphBitmap a = ksg2_char_bitmap(text + index);
    buffer_blit(buffer, x + char_number * 17, y, a.bitmap, 16, 16, color, 1);
    index += a.glyph_length;
    char_number += 1;
  }
}

void buffer_flip(void *buffer) {
  SDL_BlitScaled(buffer, &((SDL_Rect){.x = 0, .y = 0, .w = 200, .h = 200}),
                 screenSurface,
                 &((SDL_Rect){.x = 0, .y = 0, .w = 400, .h = 400}));

  SDL_UpdateWindowSurface(window);
}

int main(int argc, char *args[]) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
  } else {
    // Create window
    window = SDL_CreateWindow("Watchy CaféHaine", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
      // Get window surface
      screenSurface = SDL_GetWindowSurface(window);

      // Fill the surface white
      SDL_FillRect(screenSurface, NULL,
                   SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0xFF));

      void *watchy_buffer = new_buffer();
      buffer_clear(watchy_buffer, false);
      // buffer_set_pixel(watchy_buffer, 10, 10, true);

      // buffer_fill_rect(watchy_buffer, 20, 20, 40, 40, true);
      // buffer_draw_rect(watchy_buffer, 22, 22, 36, 36, false);

      buffer_print(watchy_buffer, 10, 10, (char *)(&"𪚲▒❿☃"), true, 1);
      buffer_print(watchy_buffer, 10, 30, (char *)(&"abcdefghij"), true, 1);

      buffer_flip(watchy_buffer);

      // Hack to get window to stay up
      SDL_Event e;
      bool quit = false;
      while (quit == false) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT)
            quit = true;
        }
      }
    }
  }
  // Destroy window
  SDL_DestroyWindow(window);

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
