#include <Adafruit_NeoPixel.h>

#include "backlight.h"
#include "keys.h"

// For keyboard indicator LED variable
#include "usb_keyboard.h"

#define STRIP_COUNT 6
#define DEFAULT_BRIGHTNESS 2
#define MAX_BRIGHTNESS 25 // Not sure what a good limit here is (could overdraw current from USB if too high)

#if DEFAULT_BRIGHTNESS > MAX_BRIGHTNESS
#undef DEFAULT_BRIGHTNESS
#define DEFAULT_BRIGHTNESS MAX_BRIGHTNESS
#endif

// DIN pins of first LED in strip
#define PIN_LED0 27
#define PIN_LED1 28
#define PIN_LED2 29
#define PIN_LED3 30
#define PIN_LED4 31
#define PIN_LED5 32

// Number of LEDs in each strip
#define LED_COUNT0 15
#define LED_COUNT1 16
#define LED_COUNT2 16
#define LED_COUNT3 13
#define LED_COUNT4 13
#define LED_COUNT5 10

// Array of all LED strips
Adafruit_NeoPixel LEDS[] = {
	Adafruit_NeoPixel(LED_COUNT5, PIN_LED5, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT4, PIN_LED4, NEO_RGB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT3, PIN_LED3, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT2, PIN_LED2, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT1, PIN_LED1, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT0, PIN_LED0, NEO_GRB + NEO_KHZ800),
};

uint8_t brightness = DEFAULT_BRIGHTNESS;

uint8_t get_brightness()
{
	return brightness;
}

uint32_t RED = 0xFF0000;
uint32_t NATURAL_WHITE = 0xFFFFBB;
uint32_t WHITE = 0xFFFFFF;
uint32_t GREEN = 0x00FF00;
uint32_t GOLD = 0xFF9900;
uint32_t MAGENTA = 0xFF00FF;
uint32_t CAPS_ENABLED_COLOR = WHITE;

uint32_t color = RED;

void backlight_setup()
{
	set_brightness(brightness);
	for (int i = 0; i < STRIP_COUNT; i++)
	{
		LEDS[i].begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
		LEDS[i].show();	 // Turn OFF all pixels ASAP
	}
	set_color(color);
}

bool function_mode = false;
bool os_enabled = true;

uint32_t get_color()
{
	return color;
}

// Basically refresh the primary background
void set_color(uint32_t color)
{
	for (int row = 0; row < STRIP_COUNT; row++)
	{
		LEDS[row].fill(color, 0, 0);
		Serial.printf("os_enabled: %d\n", os_enabled);
		if (row == Keys::CAPS_LOCK.row && (keyboard_leds & 0x2)) {
			LEDS[row].fill(CAPS_ENABLED_COLOR, Keys::CAPS_LOCK.col_led, 1);
		}
		if (row == Keys::OS.row && !os_enabled) {
			Serial.println("os enabled, turning off LED");
			LEDS[row].fill(0x000000, Keys::OS.col_led, 1);
		}
		update_row(row);
	}
}

void set_color(int row, int col, uint32_t color)
{
	LEDS[row].fill(color, col, 1);
}

// Write the current colors to given row
void update_row(int row) {
	LEDS[row].show();
}

void backlight_loop()
{
	if (function_mode)
	{
		// Write all colors to function mode color
		for (int i = 0; i < Keys::KEY_COUNT; i++)
		{
			Key k = Keys::ALL[i];
			LEDS[k.row].fill(k.function_color, k.col_led, 1);
		}
		if (os_enabled) {
			set_color(Keys::OS.row, Keys::OS.col_led, 0x00FF00);
		}
		// Show colors
		for (int row = 0; row < STRIP_COUNT; row++)
		{
			update_row(row);
		}
	}
	else
	{
		set_color(color);
	}
}

// Set the brightness ignoring MAX_BRIGHTNESS
void set_brightness_raw(uint8_t b)
{
	brightness = b;
	for (int i = 0; i < STRIP_COUNT; i++)
	{
		LEDS[i].setBrightness(brightness);
		LEDS[i].show();
	}
}

void set_brightness(uint8_t b)
{
	set_brightness_raw((b > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : b);
}

void set_function_mode(bool enabled)
{
	function_mode = enabled;
}

void set_os_enabled(bool enabled)
{
	os_enabled = enabled;
}

// TODO try to isolate the functions that call LEDS[i].show(), and try to do only 1 row per backlight update loop. This way more CPU time can be used by scanning buttons. If this creates a noticable visual animation, probably not worth it.