#include <avr/pgmspace.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// ----- BUTTON -----
const uint8_t BUTTON_PIN = 3;

// ----- DISPLAY -----
const uint8_t
	DISPLAY_WIDTH = 128,
	DISPLAY_HEIGHT = 64,
	DISPLAY_ADDRESS = 0x3C,
	DISPLAY_MAX_CHAR = 21,
	DISPLAY_MAX_LINES = 6
;
Adafruit_SSD1306 oled(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);

// ----- APPLICATIONS -----
const uint8_t TOTAL_APPS = 7;
const char apps[TOTAL_APPS][DISPLAY_MAX_CHAR-2] PROGMEM = {
	"LoveLetter",
	"StuffIWantedToSay",
	"nixxGPT",
	"Settings",
	"About",
	"App 6",
	"App 7"
};

int selectedItem;
int screenMaxItems;

// ----- TOOLS -----
char* getString(char* cstr, int cslength) {
	char buffer[cslength];
	strcpy_P(buffer, cstr);
	return buffer;
}

// ----- BOTTOM BAR HELPERS -----
void drawBottomBar(char text[DISPLAY_MAX_CHAR+1], int x = 0) {
	// line
	oled.drawLine(
		x,
		DISPLAY_HEIGHT-10,
		DISPLAY_WIDTH,
		DISPLAY_HEIGHT-10,
		1
	);
	oled.fillRect(
		x,
		DISPLAY_HEIGHT-9,
		DISPLAY_WIDTH,
		10,
		0
	);

	// bottom text
	oled.setCursor(x+1, DISPLAY_HEIGHT-8);
	oled.print(text);
}

void fillBottomBar(char text[DISPLAY_MAX_CHAR+1], int x = 0) {
	// rectangle
	oled.fillRect(
		x,
		DISPLAY_HEIGHT-10,
		DISPLAY_WIDTH,
		10,
		1
	);

	// bottom text
	oled.setCursor(x+1, DISPLAY_HEIGHT-8);
	oled.setTextColor(SSD1306_BLACK);
	oled.print(text);

	oled.setTextColor(SSD1306_WHITE);
}

// ----- BUTTON HANDLER -----
bool handleButton(char bottomText[DISPLAY_MAX_CHAR+1]) {
	bool isHeld = false;

	while (digitalRead(BUTTON_PIN)) {}
	long pressStart = millis();
	delay(80);
	while (!digitalRead(BUTTON_PIN)) {
		if (millis() - pressStart >= 200) {
			fillBottomBar(bottomText);
			oled.display();
			isHeld = true;
		}
	}

	return isHeld;
}

// ----- APPLICATIONS -----
void LoveLetter() {
	oled.clearDisplay();
	oled.setCursor(0, 0);
	oled.print("hello :3");
	oled.display();
	handleButton("Continue");
}

// ----- STARTUP -----
void setup() {
	Serial.begin(115200);

	pinMode(BUTTON_PIN, INPUT_PULLUP);

	oled.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
	Wire.setClock(400000);

	oled.setTextColor(SSD1306_WHITE);

	oled.clearDisplay();
	oled.display();
}

// ----- LOOP AS APP LAUNCHER -----
void drawAppList(int x = 0, int y = 0) {
	oled.setCursor(x, y);
	screenMaxItems = selectedItem+DISPLAY_MAX_LINES+2 > TOTAL_APPS ? TOTAL_APPS : selectedItem+DISPLAY_MAX_LINES+2;
	for (int i = selectedItem, h = 0; i < screenMaxItems; i++, h++) {
		oled.setCursor(x, y+8*h);

		char buffer[DISPLAY_MAX_CHAR-2];
		strcpy_P(buffer, apps[i]);

		oled.print(i == selectedItem ? "> ": "  ");
		oled.print(buffer);
	}
}

void loop() {
	selectedItem = 0;
	screenMaxItems = 0;

	oled.setTextWrap(false);
	for (int x = DISPLAY_WIDTH; x > 0; x = x - (x>64?32:16)) {
		oled.clearDisplay();

		drawAppList(x);
		drawBottomBar("Home", x);

		oled.display();
	} 

	while (true) {
		oled.clearDisplay();

		drawAppList();
		drawBottomBar("Home");

		oled.display();

		char buffer[DISPLAY_MAX_CHAR-2];
		strcpy_P(buffer, apps[selectedItem]);

		char bottomText[27] = "";
		sprintf(bottomText, "Launch %s", buffer);
		if (handleButton(bottomText)) {
			break;	
		} else {
			if (selectedItem != TOTAL_APPS-1) {
				for (int p = 1; p < 8; p = p+(p>3?1:2)) {
					oled.clearDisplay();

					oled.setCursor(0, -p);
					for (int i = selectedItem; i < screenMaxItems; i++) {
						oled.print(selectedItem+1 == i ? "> " : "  ");
						char buffer[DISPLAY_MAX_CHAR-2];
						strcpy_P(buffer, apps[i]);
						oled.println(buffer);
					}

					drawBottomBar("Home");

					oled.display();
				}
			} else {}

			selectedItem = selectedItem != TOTAL_APPS-1 ? selectedItem+1 : 0;
		}
	}

	switch (selectedItem) {
		case 0:
			LoveLetter();
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
	}

}
