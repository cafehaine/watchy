#include <stdint.h>
#include <stdbool.h>
#include <time.h>

// Display
void *new_buffer();
void buffer_clear(void *buffer, bool color);
void buffer_set_pixel(void *buffer, uint8_t x, uint8_t y, bool color);
void buffer_draw_rect(void *buffer, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
void buffer_fill_rect(void *buffer, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color);
void buffer_bilt(void *buffer, uint8_t x, uint8_t y, bool *bitmap, uint8_t w, uint8_t h, bool color);
void buffer_print(void *buffer, uint8_t x, uint8_t y, char *text, bool color, uint8_t scale);
void buffer_flip(void *buffer);

// Battery
bool battery_is_charging();
float battery_read_voltage();
uint8_t battery_read_percentage();

// Motor
void motor_vibrate(uint16_t duration_ms);

// RTC
/*
void *new_rtc();
struct_tm rtc_read_time(void *rtc);
void rtc_set_time(void *rtc, struct_tm time);
*/

// Bluetooth
//TODO
