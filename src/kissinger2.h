#include <stdint.h>

struct GlyphBitmap {
  uint8_t *bitmap;
  uint8_t glyph_length;
};

struct GlyphBitmap ksg2_char_bitmap(char *gliph_start);
