#include <Arduino.h>
#include "backlight.h"

#include "Keys.h"

#define DEBUG_LOOP_ENABLED 1
#define DEBUG_LOOP_TIMER 1000
// Cherry MX debounce time (ms)
#define DEBOUNCE_TIME 5

unsigned char ROW_PINS[] = { 33, 34, 35, 36, 37, 38 };
//unsigned const int ROW_PINS[] = { 3, 2 };
unsigned const int ROW_COUNT = sizeof(ROW_PINS) / sizeof(ROW_PINS[0]);
unsigned char COL_PINS[] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 14, 15, 16, 17 };
//unsigned const int COL_PINS[] = { 5, 4 };
unsigned const int COL_COUNT = sizeof(COL_PINS) / sizeof(COL_PINS[0]);

bool key_states[ROW_COUNT * COL_COUNT]; // 1D array of states, 0 = pressed
unsigned long key_times[ROW_COUNT * COL_COUNT]; // 1D array of last update per key (for debounce time)

void readKeys () {
	int index = 0; // 1 dimensional index of current key
	for (unsigned char col = 0; col < COL_COUNT; col++) {
		for (unsigned char row = 0; row < ROW_COUNT; row++) {
			digitalWrite(ROW_PINS[row], LOW); // Enable GND for this row
			//delayMicroseconds(2);
			bool key_state = digitalRead(COL_PINS[col]); // HIGH or 1 if button not pressed
			unsigned long now = millis();
			if (key_state != key_states[index] && now - key_times[index] >= DEBOUNCE_TIME) {
				key_times[index] = now; // Update last change time
				key_states[index] = key_state; // Update key state
				if (!key_state) {
					onKeyPressed(row, col);
				} else {
					onKeyReleased(row, col);
				}
			}
			digitalWrite(ROW_PINS[row], HIGH); // Disable GND for this row
			delayMicroseconds(1);
			index++;
		}
	}
}

void setup() {
	backlight_setup();
	for (unsigned char col = 0; col < COL_COUNT; col++) {
		pinMode(COL_PINS[col], INPUT_PULLUP);
	}
	for (unsigned char row = 0; row < ROW_COUNT; row++) {
		pinMode(ROW_PINS[row], OUTPUT);
		digitalWrite(ROW_PINS[row], HIGH);
	}
	for (unsigned int i = 0; i < ROW_COUNT * COL_COUNT; i++) {
		key_states[i] = 1;
	}
}

unsigned long loop_timer = 0; // Tracks loop time in microseconds
unsigned long outputtimer = 0; // Millisecond timer for loop output

void debug() {
	Serial.print(micros() - loop_timer);
	Serial.println(" microseconds");
}

void loop() {
	loop_timer = micros();
	readKeys();
	backlight_loop();
	if (millis() - outputtimer > DEBUG_LOOP_TIMER && DEBUG_LOOP_ENABLED) {
		debug();
		outputtimer = millis();
	}
	delay(1);
}

