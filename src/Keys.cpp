#include <Arduino.h>
#include "Keys.h"
#include "backlight.h"

static Key keys[6][17];

void keys_setup() {
	// Populate keys based on Keys::ALL
	for (int i = 0; i < Keys::KEY_COUNT; i++) {
		keys[Keys::ALL[i].row][Keys::ALL[i].col_switch] = Keys::ALL[i];
	}
}

// TODO turn LDR arrow keys into PREV, PAUSE/PLAY, NEXT

bool FUNCTION_MODE = false;

bool OS_ENABLED = true;
void toggle_os() {
	OS_ENABLED = !OS_ENABLED;
	set_os_enabled(OS_ENABLED);
}

void increase_brightness() {
	int brightness = get_brightness();
	brightness++;
	set_brightness(brightness);
}

void decrease_brightness() {
	int brightness = get_brightness();
	if (brightness > 0){
		brightness--;
		set_brightness(brightness);
	}
}

void num_lock() {
	Keyboard.press(KEY_NUM_LOCK);
	Keyboard.release(KEY_NUM_LOCK);
}


void onKeyPressed(int row, int col) {
	if (FUNCTION_MODE) {
		if (keys[row][col].function_bind != KEY_NULL) {
			Keyboard.press(keys[row][col].function_bind);
		}
		if (keys[row][col].function_press != NULL) {
			keys[row][col].function_press();
			return;
		} else {
			return;
		}
	}
	if (keys[row][col].keycode == KEY_FUNCTION) {
		FUNCTION_MODE = true;
		set_function_mode(FUNCTION_MODE);
		return;
	} else {
		if (!(row == Keys::OS.row && col == Keys::OS.col_switch)) {
			Keyboard.press(keys[row][col].keycode);
		} else if (OS_ENABLED) {
			Keyboard.press(keys[row][col].keycode);
		}
	}
}

void onKeyReleased(int row, int col) {
	if (FUNCTION_MODE) {
		if (keys[row][col].function_bind != KEY_NULL) {
			Keyboard.release(keys[row][col].function_bind);
		}
		if (keys[row][col].function_release != NULL) {
			keys[row][col].function_release();
		}
	}
	if (keys[row][col].keycode == KEY_FUNCTION) {
		FUNCTION_MODE = false;
		set_function_mode(FUNCTION_MODE);
		return;
	} else {
		Keyboard.release(keys[row][col].keycode);
	}
}
