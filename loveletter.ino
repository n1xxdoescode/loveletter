#include <Wire.h>
#include <Adafruit_SSD1306.h>

// ----- BUTTON -----
const uint8_t BUTTON_PIN = 7;

// ----- DISPLAY -----
const uint8_t
	DISPLAY_CLOCK = 1,
	DISPLAY_DATA = 2,
	DISPLAY_WIDTH = 128,
	DISPLAY_HEIGHT = 64,
	DISPLAY_ADDRESS = 0x3C,
	DISPLAY_MAX_CHAR = 21,
	DISPLAY_MAX_LINES = 6
;
Adafruit_SSD1306 oled(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);

// ----- FILES -----
const int loveLetterLen = 72;
const char loveLetter[loveLetterLen][DISPLAY_MAX_CHAR+1] = {
	"Dear Christine",
	"",
	"I wrote this letter ",
	"so I can express how",
	"I feel about you. ",
	"",
	"Ever since I've ",
	"known you, I've felt",
	"less depressed and ",
	"you gave me hope for",
	"love again. I ",
	"thought getting a ",
	"chance from you was ",
	"just a dream-but you",
	"actually gave more ",
	"than that. The way ",
	"you put effort on ",
	"trying to chat with ",
	"me everyday, making ",
	"me letters, coming ",
	"with me everywhere, ",
	"and those ice cream ",
	"dates? Makes me ",
	"really happy and ",
	"feel like I actually",
	"deserve to be loved ",
	"and cared. ",
	"",
	"Your stunning ",
	"beauty, cute smile, ",
	"silly laughs, long ",
	"yaps, uniqueness, ",
	"honesty, caring ",
	"personality, and ",
	"most of all, ",
	"kindness, make you ",
	"the most perfect ",
	"girl I've ever met. ",
	"I'm falling harder ",
	"for you each day and",
	"I just cant deny it.",
	"",
	"I wanted to thank ",
	"you with all my ",
	"heart for everything",
	"you've done for the ",
	"past weeks, I've ",
	"never been treated ",
	"this well in my life",
	"and I am reallyyy ",
	"greatful to have ",
	"you. I hope I'm ",
	"making you happy the",
	"same way as well, ",
	"and I sincerely ",
	"apologize if I can ",
	"be a bad person ",
	"sometimes :( but I ",
	"promise I'll try to ",
	"change my flaws and ",
	"treat you better. ",
	"",
	"That's all I wanted ",
	"to say, pleasee take",
	"care of yourself ",
	"everyday and stay ",
	"safe. I will always ",
	"be here if you need ",
	"me. thank you ",
	"again!! mwaaaa :3 ",
	"",
	"- marth <3"
};
const int aboutTextLen = 30;
const char aboutText[aboutTextLen][DISPLAY_MAX_CHAR+1] = {
	"Name",
	"- Christine",
	"Firmware",
	"- LoveBoxOS (Mara's",
	"  Edition)",
	"Firmware Version",
	"- 1.2.67",
	"GitHub Repository",
	"- https://github.com/",
	"  n1xxdoescode/lovele",
	"  tter",
	"Board",
	"- Waveshare ESP32-S3",
	"  Zero",
	"SoC",
	"- ESP32-FH4R2 2CORE",
	"  240MHz",
	"Memory",
	"- 512KB SRAM",
	"Storage",
	"- 4MB Flash",
	"Display",
	"- 0.96\" OLED 128x64",
	"  SSD1306 I2C",
	"Ambient Light",
	"- WS2812 RGB LED",
	"Input",
	"- Generic 6mm Button",
	"my heart",
	"- only yours bbg"
};

// ----- APPLICATIONS -----
const uint8_t TOTAL_APPS = 5;
const char apps[TOTAL_APPS][DISPLAY_MAX_CHAR-1]  = {
	"LoveLetter",
	"ComplimentGen",
	"StuffIWantedToSay",
	"Settings",
	"About"
};


// ----- BOTTOM BAR HELPERS -----
void drawBottomBar(char text[DISPLAY_MAX_CHAR+1]) {
	// rectangle
	oled.fillRect(
		0,
		DISPLAY_HEIGHT-11,
		DISPLAY_WIDTH,
		11,
		0
	);
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
bool handleButton(char holdText[DISPLAY_MAX_CHAR+1]) {
	bool isHeld = false;

	while (digitalRead(BUTTON_PIN)) {}
	long pressStart = millis();
	delay(80);
	while (!digitalRead(BUTTON_PIN)) {
		if (millis() - pressStart >= 500) {
			fillBottomBar(holdText);
			oled.display();
			isHeld = true;
		}
	}

	return isHeld;
}

// ----- APPLICATIONS -----
void TextViewer(const char text[][DISPLAY_MAX_CHAR+1], int textLen, char bottomText[DISPLAY_MAX_CHAR+1]) {
	int currentLine = 0;

	while (true) {
		oled.clearDisplay();

		oled.setCursor(0, 0);
		int screenMaxItems = currentLine+DISPLAY_MAX_LINES+1 > textLen ? textLen : currentLine+DISPLAY_MAX_LINES+2;
		for (int l = currentLine; l < screenMaxItems; l++) {
			oled.println(text[l]);
		}

		drawBottomBar(bottomText);

		oled.display();

		if (handleButton("Exit")) {
			break;
		} else {
			if (currentLine != textLen-1) {
				for (int p = 1; p <= 8; p++) {
					oled.clearDisplay();

					oled.setCursor(0, 0-p);
					for (int l = currentLine; l < screenMaxItems; l++) {
						oled.println(text[l]);
					}

					drawBottomBar(bottomText);

					oled.display();
				}
			} else {}

			currentLine = currentLine != textLen-1 ? currentLine+1 : 0;
		}
	}
}

void LoveLetter() {
	TextViewer(loveLetter, loveLetterLen, "03/16/2026");
}

void About() {
	TextViewer(aboutText, aboutTextLen, "About this device");
}

// ----- STARTUP -----
void setup() {
	// light stuff first
	Serial.begin(115200);

	pinMode(BUTTON_PIN, INPUT_PULLUP);

	// then display next
	Wire.begin(DISPLAY_DATA, DISPLAY_CLOCK);
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

		char bottomText[(DISPLAY_MAX_CHAR-1)+7] = "";
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
			About();
			break;
	}

}
