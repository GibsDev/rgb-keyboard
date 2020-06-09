#include <Arduino.h>
#include "Keys.h"
#include "backlight.h"

// const Key KEYS[2] = { KeyCodes::ALT, KeyCodes::ARROW_DOWN };

// Function key
const uint16_t KEY_FUNCTION = (116 | 0xF000);
// Does not exist
const uint16_t DNE = 0;

// Note: this is vertically inverted compared to the keyboard layout
const uint16_t PRIMARY_LAYOUT[6][17] = {
    {KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, DNE, DNE, DNE, KEY_SPACE, DNE, DNE, DNE, DNE, KEY_RIGHT_ALT, KEY_FUNCTION, KEY_RIGHT_CTRL, KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW},
    {KEY_LEFT_SHIFT, DNE, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, KEY_COMMA, KEY_PERIOD, KEY_SLASH, DNE, KEY_RIGHT_SHIFT, DNE, KEY_UP_ARROW, DNE},
    {KEY_CAPS_LOCK, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_QUOTE, DNE, KEY_ENTER, DNE, DNE, DNE},
    {KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_LEFT_BRACE, KEY_RIGHT_BRACE, KEY_BACKSLASH, DNE, KEY_DELETE, KEY_PAGE_DOWN},
    {KEY_TILDE, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, KEY_MINUS, KEY_EQUAL, KEY_BACKSPACE, DNE, KEY_INSERT, KEY_PAGE_UP},
    {KEY_ESC, DNE, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, DNE, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_PAUSE, KEY_PRINTSCREEN}
};

// TODO disable OS button function
// TODO turn LDR arrow keys into PREV, PAUSE/PLAY, NEXT

void volume_up() {
    Keyboard.press(KEY_MEDIA_VOLUME_INC);
    Keyboard.release(KEY_MEDIA_VOLUME_INC);
}

void volume_down() {
    Keyboard.press(KEY_MEDIA_VOLUME_DEC);
    Keyboard.release(KEY_MEDIA_VOLUME_DEC);
}

// TODO increase step size as it gets larger (make sure not to lose the same step intervals on the way down!)
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

typedef void (*VoidFunction) ();

// TODO be able to store a function or a key (if its a key the release needs to be handled properly)
// Note: this is vertically inverted compared to the keybopard layout
VoidFunction FUNCTION_LAYOUT[6][17] = {
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, decrease_brightness},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, volume_down, volume_up, NULL, NULL, NULL, increase_brightness},
    {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}
};


bool FUNCTION_MODE = false;

void onKeyPressed(int row, int col) {
    if (FUNCTION_MODE) {
        if (FUNCTION_LAYOUT[row][col] != NULL) {
            FUNCTION_LAYOUT[row][col]();
            return;
        } else {
            return;
        }
    }
    if (PRIMARY_LAYOUT[row][col] == KEY_FUNCTION) {
        FUNCTION_MODE = true;
        set_function_mode(FUNCTION_MODE);
        return;
    } else {
        Keyboard.press(PRIMARY_LAYOUT[row][col]);
    }
}

void onKeyReleased(int row, int col) {
    if (PRIMARY_LAYOUT[row][col] == KEY_FUNCTION) {
        FUNCTION_MODE = false;
        set_function_mode(FUNCTION_MODE);
        return;
    } else {
		Keyboard.release(PRIMARY_LAYOUT[row][col]);
    }
}
