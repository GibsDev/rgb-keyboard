#include <Adafruit_NeoPixel.h>

#include "backlight.h"

#define STRIP_COUNT 6
#define DEFAULT_BRIGHTNESS 3
#define MAX_BRIGHTNESS 25 // DO NOT CHANGE THIS ABOVE 7! This could overdraw current from USB!

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

/**
 * HSL Convert
 * Helper function
 */
uint8_t hsl_convert(float c, float t1, float t2) {

	if ( c < 0 ) c+=1; 
	else if ( c > 1 ) c-=1;

	if ( 6 * c < 1 ) c = t2 + ( t1 - t2 ) * 6 * c;
	else if ( 2 * c < 1 ) c = t1;
	else if ( 3 * c < 2 ) c = t2 + ( t1 - t2 ) * ( 2/3.0 - c ) * 6;
	else c = t2;
	
	return (uint8_t)(c*255); 
}

uint32_t hsl(uint16_t ih, uint8_t is, uint8_t il) {

	float h, s, l, t1, t2, tr, tg, tb;
	uint8_t r, g, b;

	h = (ih % 360) / 360.0;
	s = constrain(is, 0, 100) / 100.0;
	l = constrain(il, 0, 100) / 100.0;

	if ( s == 0 ) { 
		r = g = b = 255 * l;
		return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
	} 
	
	if ( l < 0.5 ) t1 = l * (1.0 + s);
	else t1 = l + s - l * s;
	
	t2 = 2 * l - t1;
	tr = h + 1/3.0;
	tg = h;
	tb = h - 1/3.0;

	r = hsl_convert(tr, t1, t2);
	g = hsl_convert(tg, t1, t2);
	b = hsl_convert(tb, t1, t2);

	// NeoPixel packed RGB color
	return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Note: this is based on LED index (not the same as scan index as above)
uint32_t FUNCTION_MODE_COLORS[6][17] = {
    {0, 0, 0, 0, 0, 0xFF0000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFFFFFF, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x00FF00, 0x00FF00, 0, 0, 0xFFFFFF, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

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

uint8_t get_brightness() {
	return brightness;
}

uint32_t RED = 0xFF0000;
uint32_t NATURAL_WHITE = 0xFFFFBB;
uint32_t GOLD = 0xFF9900;

uint32_t color = GOLD;

void backlight_setup() {
	set_brightness(brightness);
	for (int i = 0; i < STRIP_COUNT; i++) {
		LEDS[i].begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
		LEDS[i].show(); // Turn OFF all pixels ASAP
	}
	for (int i = 0; i < STRIP_COUNT; i++) {
		LEDS[i].fill(color, 0,0);
		// This function uses up ~0.5ms (500 microseconds) with 17 LEDs
		LEDS[i].show();
	}
}

int function_mode = false;

void rainbow_step() {
	for (int i = 0; i < STRIP_COUNT; i++) {
		LEDS[i].fill(hsl(color, 100, 50), 0, 0);
		// This function uses up ~0.5ms (500 microseconds) with 17 LEDs
		LEDS[i].show();
	}
	color++;
	if(color > 360) {
		color = 0;
	}
}

uint32_t get_color() {
	return color;
}

void set_color(uint32_t color ) {
	for (int i = 0; i < STRIP_COUNT; i++) {
		LEDS[i].fill(color, 0, 0);
		LEDS[i].show();
	}
}

void set_color(int row, int col, uint32_t color) {
	LEDS[row].fill(color, col, 1);
}

void backlight_loop() {
	if(function_mode) {
		for (int row = 0; row < STRIP_COUNT; row++) {
			for (int col = 0; col < 17; col++) {
				LEDS[row].fill(FUNCTION_MODE_COLORS[row][col], col, 1);
			}
			LEDS[row].show();
	}
	} else {
		set_color(color);
	}
}

// Set the brightness ignoring MAX_BRIGHTNESS
void set_brightness_raw(uint8_t b) {
	brightness = b;
	for (int i = 0; i < STRIP_COUNT; i++) {
		LEDS[i].setBrightness(brightness);
		LEDS[i].show();
	}
}

void set_brightness(uint8_t b) {
	set_brightness_raw((b > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : b);
}

void set_function_mode(bool enabled) {
	function_mode = enabled;
}

// TODO try to isolate the functions that call LEDS[i].show(), and try to do only 1 row per backlight update loop. This way more CPU time can be used by scanning buttons. If this creates a noticable visual animation, probably not worth it.