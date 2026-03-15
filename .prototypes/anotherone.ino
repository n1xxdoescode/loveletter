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
const uint8_t TOTAL_APPS = 5;
const char apps[TOTAL_APPS][DISPLAY_MAX_CHAR-2] = {
	"LoveLetter",
	"ComplimentGen",
	"StuffIWantedToSay",
	"Settings",
	"About"
};


// ----- BOTTOM BAR HELPERS -----
void drawBottomBar(char text[DISPLAY_MAX_CHAR+1]) {
	// line
	oled.drawLine(
		0,
		DISPLAY_HEIGHT-10,
		DISPLAY_WIDTH,
		DISPLAY_HEIGHT-10,
		1
	);

	// bottom text
	oled.setCursor(1, DISPLAY_HEIGHT-8);
	oled.print(text);
}

void fillBottomBar(char text[DISPLAY_MAX_CHAR+1]) {
	// rectangle
	oled.fillRect(
		0,
		DISPLAY_HEIGHT-10,
		DISPLAY_WIDTH,
		10,
		1
	);

	// bottom text
	oled.setCursor(1, DISPLAY_HEIGHT-8);
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
	// light stuff first
	Serial.begin(115200);

	pinMode(BUTTON_PIN, INPUT_PULLUP);

	// then display next
	oled.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
	oled.setTextColor(SSD1306_WHITE);

	oled.clearDisplay();
	oled.display();
}

// ----- LOOP AS APP LAUNCHER -----
void loop() {
	int selectedItem = 0;

	while (true) {
		oled.clearDisplay();

		drawBottomBar("Home");

		oled.setCursor(0, 0);
		int screenMaxItems = selectedItem+DISPLAY_MAX_LINES > TOTAL_APPS ? TOTAL_APPS : selectedItem+DISPLAY_MAX_LINES;
		for (int i = selectedItem; i < screenMaxItems; i++) {
			oled.print(i == selectedItem ? "> ": "  ");
			oled.println(apps[i]);
		}

		oled.display();

		char bottomText[27] = "";
		sprintf(bottomText, "Launch %s", apps[selectedItem]);
		if (handleButton(bottomText)) {
			break;	
		} else {
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
