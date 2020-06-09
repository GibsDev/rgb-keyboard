#include <Arduino.h>

#ifndef BACKLIGHT_HEADER_GUARD
#define BACKLIGHT_HEADER_GUARD

void backlight_setup();
void backlight_loop();
void set_brightness_raw(uint8_t);
void set_brightness(uint8_t);
uint8_t get_brightness();
void set_function_mode(bool);
void set_color(uint32_t);
uint32_t get_color();
void set_color(int , int, uint32_t);

#endif