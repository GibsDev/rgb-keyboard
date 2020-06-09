class Key {
    public:
    const char* name;
    unsigned char keycode;
    // unsigned int ROW
    // unsigned int COLUMN_SWITCH
    // unsigned int COLUMN_LED

    Key(const char* name, unsigned int keycode){
        name
 = name
;
        keycode = keycode;
    }
};

void onKeyPressed(int row, int col);
void onKeyReleased(int row, int col);

// The keycodes for existing keys, not necessarily corrolated to a symbol
namespace keycodes
{
    const Key ALT = Key("Alt", 18);
    const Key ARROW_DOWN = Key("Arrow Down", 40);
    const Key ARROW_LEFT = Key("Arrow Left", 37);
    const Key ARROW_RIGHT = Key("Arrow Right", 39);
    const Key ARROW_UP = Key("Arrow Up", 38);
    const Key BACKSPACE = Key("Backspace", 8);
    const Key CAPS_LOCK = Key("Caps Lock", 20);
    const Key CTRL = Key("Ctrl", 17);
    const Key INS = Key("Insert", 45);
    const Key DEL = Key("Delete", 46);
    const Key END = Key("End", 35);
    const Key HOME = Key("Home", 36);
    const Key ENTER = Key("Enter", 13);
    const Key ESC = Key("Esc", 27);
    const Key F1 = Key("F1", 112);
    const Key F2 = Key("F2", 113);
    const Key F3 = Key("F3", 114);
    const Key F4 = Key("F4", 115);
    const Key F5 = Key("F5", 116);
    const Key F6 = Key("F6", 117);
    const Key F7 = Key("F7", 118);
    const Key F8 = Key("F8", 119);
    const Key F9 = Key("F9", 120);
    const Key F10 = Key("F10", 121);
    const Key F11 = Key("F11", 122);
    const Key F12 = Key("F12", 123);
    const Key NUM_LOCK = Key("Num Lock", 144);
    const Key NUMPAD_SUBTRACT = Key("(NumPad) -", 109);
    const Key NUMPAD_MULTIPLY = Key("(NumPad) *", 106);
    const Key NUMPAD_DECIMAL = Key("(NumPad) .", 110);
    const Key NUMPAD_DIVIDE = Key("(NumPad) /", 111);
    const Key NUMPAD_ADD = Key("(NumPad) +", 107);
    const Key NUMPAD_0 = Key("(NumPad) 0", 96);
    const Key NUMPAD_1 = Key("(NumPad) 1", 97);
    const Key NUMPAD_2 = Key("(NumPad) 2", 98);
    const Key NUMPAD_3 = Key("(NumPad) 3", 99);
    const Key NUMPAD_4 = Key("(NumPad) 4", 100);
    const Key NUMPAD_5 = Key("(NumPad) 5", 101);
    const Key NUMPAD_6 = Key("(NumPad) 6", 102);
    const Key NUMPAD_7 = Key("(NumPad) 7", 103);
    const Key NUMPAD_8 = Key("(NumPad) 8", 104);
    const Key NUMPAD_9 = Key("(NumPad) 9", 105);
    const Key PAGE_DOWN = Key("Page Down", 32);
    const Key PAGE_UP = Key("Page Up", 33);
    const Key PAUSE = Key("Pause", 19);
    const Key PRINT_SCRN = Key("Print Scrn", 44);
    const Key SCROLL_LOCK = Key("Scroll Lock", 145);
    const Key SHIFT = Key("Shift", 16);
    const Key SPACE = Key("Space", 32);
    const Key TAB = Key("Tab", 9);
    const Key A = Key("A", 65);
    const Key B = Key("B", 66);
    const Key C = Key("C", 67);
    const Key D = Key("D", 68);
    const Key E = Key("E", 69);
    const Key F = Key("F", 70);
    const Key G = Key("G", 71);
    const Key H = Key("H", 72);
    const Key I = Key("I", 73);
    const Key J = Key("J", 74);
    const Key K = Key("K", 75);
    const Key L = Key("L", 76);
    const Key M = Key("M", 77);
    const Key N = Key("N", 78);
    const Key O = Key("O", 79);
    const Key P = Key("P", 80);
    const Key Q = Key("Q", 81);
    const Key R = Key("R", 82);
    const Key S = Key("S", 83);
    const Key T = Key("T", 84);
    const Key U = Key("U", 85);
    const Key V = Key("V", 86);
    const Key W = Key("W", 87);
    const Key X = Key("X", 88);
    const Key Y = Key("Y", 89);
    const Key Z = Key("Z", 90);
    const Key NUM_0 = Key("0", 48);
    const Key NUM_1 = Key("1", 49);
    const Key NUM_2 = Key("2", 50);
    const Key NUM_3 = Key("3", 51);
    const Key NUM_4 = Key("4", 52);
    const Key NUM_5 = Key("5", 53);
    const Key NUM_6 = Key("6", 54);
    const Key NUM_7 = Key("7", 55);
    const Key NUM_8 = Key("8", 56);
    const Key NUM_9 = Key("9", 57);
    const Key APOSTROPHE = Key("Apostrophe (')", 222);
    const Key MINUS = Key("Minus (-)", 189);
    const Key COMMA = Key("Comma (,)", 188);
    const Key PERIOD = Key("Period (.)", 190);
    const Key FORWARD_SLASH = Key("Forward Slash (/)", 191);
    const Key SEMI_COLON = Key("Semi Colon (;)", 186);
    const Key OPEN_BRACKET = Key("Open Brack ([)", 219);
    const Key BACKSLASH = Key("Backslash (\\)", 220);
    const Key CLOSE_BRACKET = Key("Close Bracket (])", 221);
    const Key BACKQUOTE = Key("Backquote (`)", 192);
    const Key EQUALS = Key("Equals (=)", 187);
    const Key OS = Key("OS", 91);
} // namspace Keys


extern const Key KEYS[2];