#include <Adafruit_NeoPixel.h>

#define STRIP_COUNT 6
#define DEFAULT_BRIGHTNESS 10
#define MAX_BRIGHTNESS 10 // DO NOT CHANGE THIS ABOVE 7! This could overdraw current from USB!

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


// Array of all LED strips
Adafruit_NeoPixel LEDS[] = {
	Adafruit_NeoPixel(LED_COUNT0, PIN_LED0, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT1, PIN_LED1, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT2, PIN_LED2, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT3, PIN_LED3, NEO_GRB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT4, PIN_LED4, NEO_RGB + NEO_KHZ800),
	Adafruit_NeoPixel(LED_COUNT5, PIN_LED5, NEO_GRB + NEO_KHZ800),
};

void backlight_setup() {
	for (int i = 0; i < STRIP_COUNT; i++) {
		LEDS[i].setBrightness(DEFAULT_BRIGHTNESS);
		LEDS[i].begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
		LEDS[i].show(); // Turn OFF all pixels ASAP
	}
}

int color = 0;

void backlight_loop() {
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

void set_row_brightness(int i, uint8_t b) {
	LEDS[i].setBrightness((b > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : b);
}

void set_brightness(uint8_t b) {
	for (int i = 0; i < STRIP_COUNT; i++) {
		set_row_brightness(i, b);
	}
}
