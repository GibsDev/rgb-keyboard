typedef void (*void_function_t)();

class Key
{
public:
	const char *name;
	uint16_t keycode; // The teensyduino keycode
	uint8_t row;
	uint8_t col_switch;
	uint8_t col_led;
	void_function_t function;
	uint32_t function_color;

	Key(const char *name, uint16_t keycode, uint8_t row, uint8_t col_switch, uint8_t col_led)
	{
		this->name = name;
		this->keycode = keycode;
		this->row = row;
		this->col_switch = col_switch;
		this->col_led = col_led;
	}

	void set_function_color(uint32_t color)
	{
		this->function_color = color;
	}

	void set_function(void_function_t func)
	{
		this->function = func;
	}

	void run_function()
	{
		this->function();
	}
};

void onKeyPressed(int row, int col);
void onKeyReleased(int row, int col);

const uint16_t KEY_FUNCTION = (116 | 0xF000);

// Physically available keys
namespace Keys
{
	const Key ALT_LEFT = Key("Alt Left", KEY_LEFT_ALT, 0, 2, 2);
	const Key ALT_RIGHT = Key("Alt Right", KEY_RIGHT_ALT, 0, 11, 4);
	const Key ARROW_DOWN = Key("Arrow Down", KEY_DOWN_ARROW, 0, 15, 8);
	const Key ARROW_LEFT = Key("Arrow Left", KEY_LEFT_ARROW, 0, 14, 7);
	const Key ARROW_RIGHT = Key("Arrow Right", KEY_RIGHT_ARROW, 0, 16, 9);
	const Key ARROW_UP = Key("Arrow Up", KEY_UP_ARROW, 1, 15, 13);
	const Key BACKSPACE = Key("Backspace", KEY_BACKSPACE, 4, 13, 13);
	const Key CAPS_LOCK = Key("Caps Lock", KEY_CAPS_LOCK, 2, 0, 0);
	const Key CTRL_LEFT = Key("Ctrl Left", KEY_LEFT_CTRL, 0, 0, 0);
	const Key CTRL_RIGHT = Key("Ctrl Right", KEY_RIGHT_CTRL, 0, 14, 6);
	const Key INS = Key("Insert", KEY_INSERT, 4, 15, 14);
	const Key DEL = Key("Delete", KEY_DELETE, 3, 15, 14);
	const Key ENTER = Key("Enter", KEY_ENTER, 2, 13, 12);
	const Key ESC = Key("Esc", KEY_ESC, 5, 0, 0);
	const Key F1 = Key("F1", KEY_F1, 5, 2, 1);
	const Key F2 = Key("F2", KEY_F2, 5, 3, 2);
	const Key F3 = Key("F3", KEY_F3, 5, 4, 3);
	const Key F4 = Key("F4", KEY_F4, 5, 5, 4);
	const Key F5 = Key("F5", KEY_F5, 5, 6, 5);
	const Key F6 = Key("F6", KEY_F6, 5, 7, 6);
	const Key F7 = Key("F7", KEY_F7, 5, 8, 7);
	const Key F8 = Key("F8", KEY_F8, 5, 9, 8);
	const Key F9 = Key("F9", KEY_F9, 5, 11, 9);
	const Key F10 = Key("F10", KEY_F10, 5, 12, 10);
	const Key F11 = Key("F11", KEY_F11, 5, 13, 11);
	const Key F12 = Key("F12", KEY_F12, 5, 14, 12);
	const Key PAGE_DOWN = Key("Page Down", KEY_PAGE_DOWN, 3, 16, 15);
	const Key PAGE_UP = Key("Page Up", KEY_PAGE_UP, 4, 16, 15);
	const Key PAUSE = Key("Pause", KEY_PAUSE, 5, 15, 13);
	const Key PRINT_SCRN = Key("Print Scrn", KEY_PRINTSCREEN, 5, 16, 14);
	const Key SHIFT_LEFT = Key("Shift", KEY_LEFT_SHIFT, 1, 0, 0);
	const Key SHIFT_RIGHT = Key("Shift", KEY_RIGHT_SHIFT, 1, 13, 11);
	const Key SPACE = Key("Space", KEY_SPACE, 0, 6, 3);
	const Key TAB = Key("Tab", KEY_TAB, 3, 0, 0);
	const Key A = Key("A", KEY_A, 2, 1, 1);
	const Key B = Key("B", KEY_B, 1, 6, 5);
	const Key C = Key("C", KEY_C, 1, 4, 3);
	const Key D = Key("D", KEY_D, 2, 3, 3);
	const Key E = Key("E", KEY_E, 3, 3, 3);
	const Key F = Key("F", KEY_F, 2, 4, 4);
	const Key G = Key("G", KEY_G, 2, 5, 5);
	const Key H = Key("H", KEY_H, 2, 6, 6);
	const Key I = Key("I", KEY_I, 3, 8, 8);
	const Key J = Key("J", KEY_J, 2, 7, 7);
	const Key K = Key("K", KEY_K, 2, 8, 8);
	const Key L = Key("L", KEY_L, 2, 9, 9);
	const Key M = Key("M", KEY_M, 1, 8, 7);
	const Key N = Key("N", KEY_N, 1, 7, 6);
	const Key O = Key("O", KEY_O, 3, 9, 9);
	const Key P = Key("P", KEY_P, 3, 10, 10);
	const Key Q = Key("Q", KEY_Q, 3, 1, 1);
	const Key R = Key("R", KEY_R, 3, 4, 4);
	const Key S = Key("S", KEY_S, 2, 2, 2);
	const Key T = Key("T", KEY_T, 3, 5, 5);
	const Key U = Key("U", KEY_U, 3, 7, 7);
	const Key V = Key("V", KEY_V, 1, 5, 4);
	const Key W = Key("W", KEY_W, 3, 2, 2);
	const Key X = Key("X", KEY_X, 1, 3, 2);
	const Key Y = Key("Y", KEY_Y, 3, 6, 6);
	const Key Z = Key("Z", KEY_Z, 1, 2, 1);
	const Key NUM_0 = Key("0", KEY_0, 4, 10, 10);
	const Key NUM_1 = Key("1", KEY_1, 4, 1, 1);
	const Key NUM_2 = Key("2", KEY_2, 4, 2, 2);
	const Key NUM_3 = Key("3", KEY_3, 4, 3, 3);
	const Key NUM_4 = Key("4", KEY_4, 4, 4, 4);
	const Key NUM_5 = Key("5", KEY_5, 4, 5, 5);
	const Key NUM_6 = Key("6", KEY_6, 4, 6, 6);
	const Key NUM_7 = Key("7", KEY_7, 4, 7, 7);
	const Key NUM_8 = Key("8", KEY_8, 4, 8, 8);
	const Key NUM_9 = Key("9", KEY_9, 4, 9, 9);
	const Key APOSTROPHE = Key("Apostrophe (')", KEY_QUOTE, 2, 11, 11);
	const Key MINUS = Key("Minus (-)", KEY_MINUS, 4, 11, 11);
	const Key COMMA = Key("Comma (,)", KEY_COMMA, 1, 9, 8);
	const Key PERIOD = Key("Period (.)", KEY_PERIOD, 1, 10, 9);
	const Key FORWARD_SLASH = Key("Forward Slash (/)", KEY_SLASH, 1, 11, 10);
	const Key SEMI_COLON = Key("Semi Colon (;)", KEY_SEMICOLON, 2, 10, 10);
	const Key LEFT_BRACE = Key("Left Brace ([)", KEY_LEFT_BRACE, 3, 11, 11);
	const Key RIGHT_BRACE = Key("Right Brace (])", KEY_RIGHT_BRACE, 3, 12, 12);
	const Key BACKSLASH = Key("Backslash (\\)", KEY_BACKSLASH, 3, 13, 13);
	const Key TILDE = Key("Tilde (`)", KEY_TILDE, 4, 0, 0);
	const Key EQUALS = Key("Equals (=)", KEY_EQUAL, 4, 12, 12);
	const Key OS = Key("OS", KEY_LEFT_GUI, 0, 1, 1);
	const Key FUNCTION = Key("Function", KEY_FUNCTION, 0, 12, 5);
	const Key ALL[83] = {
		ALT_LEFT, ALT_RIGHT, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT, ARROW_UP, BACKSPACE, CAPS_LOCK, CTRL_LEFT, CTRL_RIGHT, INS, DEL, ENTER, ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PAGE_DOWN, PAGE_UP, PAUSE, PRINT_SCRN, SHIFT_LEFT, SHIFT_RIGHT, SPACE, TAB, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, APOSTROPHE, MINUS, COMMA, PERIOD, FORWARD_SLASH, SEMI_COLON, LEFT_BRACE, RIGHT_BRACE, BACKSLASH, TILDE, EQUALS, OS, FUNCTION};
	// const Key HOME = Key("Home");
	// const Key END = Key("End");
	// const Key NUM_LOCK = Key("Num Lock");
	// const Key NUMPAD_SUBTRACT = Key("(NumPad) -");
	// const Key NUMPAD_MULTIPLY = Key("(NumPad) *");
	// const Key NUMPAD_DECIMAL = Key("(NumPad) .");
	// const Key NUMPAD_DIVIDE = Key("(NumPad) /");
	// const Key NUMPAD_ADD = Key("(NumPad) +");
	// const Key NUMPAD_0 = Key("(NumPad) 0");
	// const Key NUMPAD_1 = Key("(NumPad) 1");
	// const Key NUMPAD_2 = Key("(NumPad) 2");
	// const Key NUMPAD_3 = Key("(NumPad) 3");
	// const Key NUMPAD_4 = Key("(NumPad) 4");
	// const Key NUMPAD_5 = Key("(NumPad) 5");
	// const Key NUMPAD_6 = Key("(NumPad) 6");
	// const Key NUMPAD_7 = Key("(NumPad) 7");
	// const Key NUMPAD_8 = Key("(NumPad) 8");
	// const Key NUMPAD_9 = Key("(NumPad) 9");
	// const Key SCROLL_LOCK = Key("Scroll Lock");
} // namespace keycodes

extern const Key KEYS[2];