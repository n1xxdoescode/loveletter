#include <Wire.h>
#include <Adafruit_SSD1306.h>

// ----- BUTTON -----
const uint8_t BUTTON_PIN = 6;

// ----- DISPLAY -----
const uint8_t
	DISPLAY_CLOCK = 1,
	DISPLAY_DATA = 2,
	DISPLAY_WIDTH = 128,
	DISPLAY_ADDRESS = 0x3C,
	DISPLAY_MAX_CHAR = 21,
	DISPLAY_MAX_LINES = 6
;
uint8_t DISPLAY_HEIGHT = 64;
Adafruit_SSD1306 oled(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, -1);

// ----- BOTTOM BAR HELPERS -----
void drawBottomBar(char text[DISPLAY_MAX_CHAR+1], const unsigned char icon[8]) {
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

	oled.drawBitmap(DISPLAY_WIDTH-10, DISPLAY_HEIGHT-8, icon, 8, 8, 1);
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
		if (millis() - pressStart >= 300) {
			fillBottomBar(holdText);
			oled.display();
			isHeld = true;
		}
	}

	return isHeld;
}

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
	"met you, I've felt",
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
	"dates? Make me ",
	"really happy and ",
	"feel like I actually",
	"deserve to be loved ",
	"and cared for. ",
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
	"girl in my eyes. ",
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
const int aboutTextLen = 32;
const char aboutText[aboutTextLen][DISPLAY_MAX_CHAR+1] = {
	"Name",
	"- Christine",
	"Device",
	"- LoveBoard OLED",
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
const int siwtsLen = 17;
const char siwts[siwtsLen][96] = {
	"you're the cutest\nthing ever",
	"i really like your\npersonality :3",
	"you make my heart\nmelt",
	"always eat on time,\nokay??",
	"you're the best thing\nthat happened to me",
	"i wish we could hang\nout more",
	"i really love it when\nwe link arms (i wish\nfor holding hands\nnext HEHEHE)",
	"this device shows how\nmuch effort i can\ndo for us :3",
	"i am very glad that i\nmet you :3",
	"i really love being\nby your side",
	"just so you know,\nyour smile is the\nmost beautiful\nthing ever",
	"sorry for being\nstupid or bad\nsometimes :(",
	"i am willing to\nchange my bad habits\njust for you",
	"= me + you\n= meant to be",
	"sorry for being ugly\nToT",
	"your imperfections\nmake you 101\%\nperfect :3",
	"please dont leave me"
};

// ----- APPLICATIONS -----
const uint8_t TOTAL_APPS = 5;
const char apps[TOTAL_APPS][DISPLAY_MAX_CHAR-1]  = {
	"LoveLetter",
	"StuffIWantedToSay",
	"nixxGPT",
	"Settings",
	"About"
};
const unsigned char icons[TOTAL_APPS+2][8] = {
	{
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000,
		0b00000000
	},
	{
		0b00011000,
		0b00111100,
		0b01111110,
		0b11111111,
		0b01000010,
		0b01000010,
		0b01111110,
		0b00000000
	},
	{
		0b00000000,
		0b01111110,
		0b11000011,
		0b10100101,
		0b10011001,
		0b10000001,
		0b11111111,
		0b00000000
	},
	{
		0b01100110,
		0b10011001,
		0b10000001,
		0b10000001,
		0b01000010,
		0b00100100,
		0b00011000,
		0b00000000
	},
	{
		0b00000000,
		0b00000000,
		0b00011000,
		0b00011000,
		0b00000000,
		0b00111100,
		0b01000010,
		0b00000000
	},
	{
		0b00000000,
		0b01111110,
		0b00000000,
		0b01111110,
		0b00000000,
		0b01111110,
		0b00000000,
		0b00000000
	},
	{
		0b00111000,
		0b01000100,
		0b10010010,
		0b10000010,
		0b10010010,
		0b01010100,
		0b00111000,
		0b00000000
	}
};

void TextViewer(const char text[][DISPLAY_MAX_CHAR+1], int textLen, char bottomText[DISPLAY_MAX_CHAR+1], const unsigned char icon[8]) {
	int currentLine = 0;

	while (true) {
		oled.clearDisplay();

		oled.setCursor(0, 0);
		int screenMaxItems = currentLine+DISPLAY_MAX_LINES+2 > textLen ? textLen : currentLine+DISPLAY_MAX_LINES+2;
		for (int l = currentLine; l < screenMaxItems; l++) {
			oled.println(text[l]);
		}

		drawBottomBar(bottomText, icon);

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

					drawBottomBar(bottomText, icon);

					oled.display();
				}
			} else {}

			currentLine = currentLine != textLen-1 ? currentLine+1 : 0;
		}
	}
}

void LoadingScreen(char bottomText[DISPLAY_MAX_CHAR-1], const unsigned char icon[8]) {
	for (int p = -30; p <= DISPLAY_WIDTH; p = p+2) {
		oled.clearDisplay();

		oled.drawLine(p, DISPLAY_HEIGHT-10, p+30, DISPLAY_HEIGHT-10, 1);

		oled.drawBitmap(1, DISPLAY_HEIGHT-8, icon, 8, 8, 1);

		oled.setCursor(11, DISPLAY_HEIGHT-8);
		oled.print(bottomText);

		oled.display();
	}
}

void LoveLetter() {
	TextViewer(loveLetter, loveLetterLen, "03/16/2026", icons[2]);
}

void StuffIWantedToSay() {
	int currentMessage = 0;

	while (true) {
		oled.clearDisplay();

		oled.setCursor(0, 0);
		oled.print(siwts[currentMessage]);

		drawBottomBar("Marth says...", icons[3]);

		oled.display();

		if (handleButton("Exit")) {
			break;
		} else {
			currentMessage = currentMessage != siwtsLen-1 ? currentMessage+1 : 0;
		}
	}
}

void Settings() {
	bool isRunning = true;

	const uint8_t TOTAL_SETTINGS = 3;
	char settings[TOTAL_SETTINGS][DISPLAY_MAX_CHAR-1] = {
		"Brightness",
		"High Refresh Mode",
		"Back"
	};

	while (isRunning) {
		int selectedItem = 0;

		while (true) {
			oled.clearDisplay();

			oled.setCursor(0, 0);
			int screenMaxItems = selectedItem+DISPLAY_MAX_LINES+2 > TOTAL_SETTINGS ? TOTAL_SETTINGS : selectedItem+DISPLAY_MAX_LINES+2;
			for (int i = selectedItem; i < screenMaxItems; i++) {
				oled.print(selectedItem == i ? "> " : "  ");
				oled.println(settings[i]);
			}

			drawBottomBar("Settings", icons[5]);

			oled.display();

			if (handleButton(settings[selectedItem])) {
				break;
			} else {
				if (selectedItem != TOTAL_SETTINGS-1) {
					for (int p = 1; p <= 8; p++) {
						oled.clearDisplay();

						oled.setCursor(0, 0-p);
						for (int i = selectedItem; i < screenMaxItems; i++) {
							oled.print("  ");
							oled.println(settings[i]);
						}

						oled.setCursor(0, 0);
						oled.print(">");

						drawBottomBar("Settings", icons[5]);

						oled.display();
					}
				}
				selectedItem = selectedItem != TOTAL_SETTINGS-1 ? selectedItem+1 : 0;
			}
		}
		switch (selectedItem) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				isRunning = false;
				break;
		}
	}
}

void About() {
	TextViewer(aboutText, aboutTextLen, "About this device", icons[6]);
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

	for (int i = 0; i < 2; i++) {
		for (int p = -30; p <= DISPLAY_WIDTH; p = p+2) {
			oled.clearDisplay();

			oled.setTextSize(2);
			oled.setCursor(0, 0);
			oled.print("LoveBox");
			oled.setTextSize(1);
			oled.setCursor(0, 16);
			if (DISPLAY_HEIGHT == 64) {
				oled.print("Mara's Edition");
			}

			oled.drawLine(p, DISPLAY_HEIGHT-10, p+30, DISPLAY_HEIGHT-10, 1);
			oled.setCursor(1, DISPLAY_HEIGHT-8);
			oled.print("Starting up...");

			oled.display();
		}
	}
	for (int p = DISPLAY_WIDTH; p > 0; p = p - 4) {
		oled.clearDisplay();

		oled.drawLine(p, DISPLAY_HEIGHT-10, DISPLAY_WIDTH-1, DISPLAY_HEIGHT-10, 1);

		oled.display();
	}	
}

// ----- LOOP AS APP LAUNCHER -----
void loop() {
	int selectedItem = 0;

	for (int p = DISPLAY_HEIGHT; p > 0; p = p - 4) {
		oled.clearDisplay();

		oled.setCursor(0, p);
		int screenMaxItems = selectedItem+DISPLAY_MAX_LINES+2 > TOTAL_APPS ? TOTAL_APPS : selectedItem+DISPLAY_MAX_LINES+2;
		for (int i = selectedItem; i < TOTAL_APPS; i++) {
			oled.print("  ");
			oled.println(apps[i]);
		}

		drawBottomBar("Home", icons[1]);

		oled.display();
	}

	while (true) {
		oled.clearDisplay();

		oled.setCursor(0, 0);
		int screenMaxItems = selectedItem+DISPLAY_MAX_LINES+2 > TOTAL_APPS ? TOTAL_APPS : selectedItem+DISPLAY_MAX_LINES+2;
		for (int i = selectedItem; i < screenMaxItems; i++) {
			oled.print("  ");
			oled.println(apps[i]);
		}

		oled.drawBitmap(2, 0, icons[selectedItem+2], 8, 8, 1);

		drawBottomBar("Home", icons[1]);

		oled.display();

		char bottomText[(DISPLAY_MAX_CHAR-1)+7] = "";
		sprintf(bottomText, "Launch %s", apps[selectedItem]);
		if (handleButton(bottomText)) {
			break;	
		} else {
			for (int p = 1; p <= 8; p++) {
				oled.clearDisplay();

				oled.setCursor(0, 0-p);
				for (int l = selectedItem; l < screenMaxItems; l++) {
					oled.print("  ");
					oled.println(apps[l]);
				}

				drawBottomBar("Home", icons[1]);

				oled.display();
			}
			selectedItem = selectedItem+1;
			if (selectedItem == TOTAL_APPS) {
				break;
			}
		}
	}

	switch (selectedItem) {
		case 0:
			LoadingScreen("LoveLetter", icons[2]);
			LoveLetter();
			break;
		case 1:
			LoadingScreen("StuffIWantedToSay", icons[3]);
			StuffIWantedToSay();
			break;
		case 2:
			break;
		case 3:
			LoadingScreen("Settings", icons[5]);
			Settings();
			break;
		case 4:
			LoadingScreen("About", icons[6]);
			About();
			break;
	}

}
