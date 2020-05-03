#include <Adafruit_NeoPixel.h>

#define STRIP_COUNT 1
#define DEFAULT_BRIGHTNESS 7
#define MAX_BRIGHTNESS 7 // DO NOT CHANGE THIS ABOVE 7! This could overdraw current from USB!

#if DEFAULT_BRIGHTNESS > MAX_BRIGHTNESS
	#undef DEFAULT_BRIGHTNESS
	#define DEFAULT_BRIGHTNESS MAX_BRIGHTNESS
#endif

// For test strip only
#define PIN_LED 22
#define LED_COUNT 4

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
	Adafruit_NeoPixel(17, PIN_LED, NEO_GRB + NEO_KHZ800),
//	Adafruit_NeoPixel(LED_COUNT0, LED_PIN0, NEO_GRB + NEO_KHZ800),
//	Adafruit_NeoPixel(LED_COUNT1, LED_PIN1, NEO_GRB + NEO_KHZ800),
//	Adafruit_NeoPixel(LED_COUNT2, LED_PIN2, NEO_GRB + NEO_KHZ800),
//	Adafruit_NeoPixel(LED_COUNT3, LED_PIN3, NEO_GRB + NEO_KHZ800),
//	Adafruit_NeoPixel(LED_COUNT4, LED_PIN4, NEO_GRB + NEO_KHZ800),
//	Adafruit_NeoPixel(LED_COUNT5, LED_PIN5, NEO_GRB + NEO_KHZ800),
};

void backlight_setup() {
	for (int i = 0; i < STRIP_COUNT; i++) {
		LEDS[i].setBrightness(DEFAULT_BRIGHTNESS);
		LEDS[i].begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
		LEDS[i].show(); // Turn OFF all pixels ASAP
	}
	LEDS[0].fill(0xFFFFBB, 0, 0);
	LEDS[0].show();
}

void backlight_loop() {
	LEDS[0].fill(0xFFFFBB, 0, 0);
	// This function uses up ~0.5ms (500 microseconds) with 17 LEDs
	LEDS[0].show();
}

void set_row_brightness(int i, uint8_t b) {
	LEDS[i].setBrightness((b > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : b);
}

void set_brightness(uint8_t b) {
	for (int i = 0; i < STRIP_COUNT; i++) {
		set_row_brightness(i, b);
	}
}
