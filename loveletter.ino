#include <Preferences.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// ----- BUTTON -----
const uint8_t BUTTON_PIN = 6;

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

// ----- PREFERENCES -----
Preferences prefs;

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
const int confessionLetterLen = 52;
const char confessionLetter[confessionLetterLen][DISPLAY_MAX_CHAR+1] = {
	"We may not have met ",
	"each other yet ",
	"before, but when the",
	"first time I saw ",
	"you, I thought you ",
	"were just another ",
	"girl that just ",
	"happened to be ",
	"caught by my eyes. ",
	"Days pass by, I ",
	"started seeing you ",
	"frequently, and I ",
	"feel like i'm ",
	"getting signs. To be",
	"honest, I was slowly",
	"developing feelings ",
	"for you because of ",
	"your looks at that ",
	"time and it only got",
	"huge after. I was ",
	"very shy to approach",
	"you before so I went",
	"to my friend Raein, ",
	"which happens to be ",
	"your friend too, and",
	"asked him some ",
	"things about you, ",
	"and yes, my feelings",
	"just got bigger. ",
	"After that, I ",
	"started to admire ",
	"you from afar each ",
	"time I see you. ",
	"Since the school ",
	"year is about to ",
	"end, I came here to ",
	"confess what I feel ",
	"for you so I can ",
	"finally let it out. ",
	"I like you and ",
	"theres no reason I ",
	"can deny, you're the",
	"most unique girl ",
	"i've ever seen and ",
	"your personality ",
	"makes you even more ",
	"attractive to me. I ",
	"really don't expect ",
	"too much soo any ",
	"answer would be fine",
	":> That's all, take ",
	"care! "
};
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
	"grateful to have ",
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
const int aboutTextLen = 36;
const char aboutText[aboutTextLen][DISPLAY_MAX_CHAR+1] = {
	"Name",
	"- Christine",
	"Device",
	"- LoveBoard OLED",
	"Firmware",
	"- LoveBoxOS",
	"  (Mara's Edition)",
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
	"my crush",
	"- no other than you",
	"how much i adore you",
	"- a lot",
	"my heart",
	"- only yours bbg"
};
const int loveBoxLen = 25;
const char loveBox[loveBoxLen][96] = {
	"i could stare at\nyou for hours",
	"i really like your\npersonality :3",
	"you make my heart\nmelt",
	"always eat on time,\nokay??",
	"you're the best thing\nthat's happened to me",
	"i wish we could hang\nout more",
	"you're the prettiest\ngirl ever frfr",
	"i have a crush on\nyou...",
	"i really love it when\nwe link arms (i wish\nfor holding hands\nnext HEHEHE)",
	"this device shows how\nmuch effort i can\ndo for us :3",
	"i am very glad that i\nmet you :3",
	"in a field full of\nflowers, you're\nthe one that i'd\npick<3",
	"i really love being\nclingy around you",
	"just so you know,\nyour smile is the\nmost beautiful\nthing ever",
	"i really, really\nmiss you :(",
	"i think about you\nalmost every minute",
	"sorry for being\nstupid or immature\nsometimes :(",
	"do you still like me?",
	"i really love it when\nyoure honest on\nsomething :)",
	"i am willing to\nchange my bad habits\njust for you",
	"= me + you\n= meant to be\nYIEEEHEHEHEHEEE",
	"sorry for being ugly\nToT",
	"your imperfections\nmake you 101\%\nperfect :3",
	"please dont leave me",
	"thank you for always\nbeing there at my\nlowest :)"
};

// ----- APPLICATIONS -----
const uint8_t TOTAL_APPS = 6;
const char apps[TOTAL_APPS][DISPLAY_MAX_CHAR-1]  = {
	"Tutorial",
	"LoveLetter",
	"LoveBox",
	"MovingHearts",
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
		0b00111100,
		0b01000010,
		0b01000010,
		0b01000010,
		0b00111100,
		0b00000000,
		0b00111100,
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
		0b00000111,
		0b00000001,
		0b01010001,
		0b10101000,
		0b10001000,
		0b01010000,
		0b00100000,
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

bool Dialog(char prompt[84], char bottomText[DISPLAY_MAX_CHAR+1], char bottomTextAgree[DISPLAY_MAX_CHAR+1], const unsigned char icon[8]) {
	oled.clearDisplay();

	oled.setTextSize(1);
	oled.setCursor(0, 0);
	oled.print(prompt);

	drawBottomBar(bottomText, icon);

	oled.display();

	return handleButton(bottomTextAgree);
}

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
			return;
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

int Menu(const int itemsLen, const char items[][DISPLAY_MAX_CHAR-1], char bottomText[DISPLAY_MAX_CHAR+1], char bottomTextAgree[DISPLAY_MAX_CHAR+1], const unsigned char icon[8]) {
	int selectedItem = 0;

	while (true) {
		oled.clearDisplay();

		oled.setCursor(0, 0);
		int screenMaxItems = selectedItem+DISPLAY_MAX_LINES+2 > itemsLen ? itemsLen : selectedItem+DISPLAY_MAX_LINES+2;
		for (int i = selectedItem; i < screenMaxItems; i++) {
			oled.print(i == selectedItem ? "> " : "  ");
			oled.println(items[i]);
		}

		drawBottomBar(bottomText, icon);

		oled.display();

		if (handleButton(bottomTextAgree)) {
			return selectedItem;
		} else {
			if (selectedItem != itemsLen-1) {
				for (int p = 1; p <= 8; p++) {
					oled.clearDisplay();

					oled.setCursor(0, 0-p);
					for (int i = selectedItem; i < screenMaxItems; i++) {
						oled.print("  ");
						oled.println(items[i]);
					}

					oled.setCursor(0, 0);
					oled.print(">");

					drawBottomBar(bottomText, icon);

					oled.display();
				}
			}
			selectedItem = selectedItem != itemsLen-1 ? selectedItem+1 : 0;
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

void Tutorial() {
	Dialog("Haiii Maraaa!\nIt seems like it's\nyour first time using\nthis, let me help!", "Press Button ->", "sure why not", icons[0]);
	while (true) {
		if (!Dialog("To cycle between\nitems or scroll text,\nsimply press the\nbutton!\n(Press the button)", "Tutorial", "bro i said press", icons[2])) {break;}
	}
	while (true) {
		if (!Dialog("To select an item\nor exit a screen,\npress and hold!\n(Press and hold)", "Tutorial", "You got it!", icons[2])) {
			if (Dialog("bro i said hold", "click to try again", "okay my bad my bad", icons[0])) {break;}
		} else {
			break;
		}
	}
	Dialog("You've completed the\ntutorial! I hope you\nlike my little gift:)\n\nmade with love,\nmarth :)", "Tutorial", "okay thanks bye", icons[2]);
}

void LoveLetter() {
	const int lettersLen = 3;
	const char letters[lettersLen][DISPLAY_MAX_CHAR-1] = {
		"[!] Mar. 16, 2026",
		"Feb. 9, 2026",
		"Back"
	};

	while (true) {
		switch (Menu(lettersLen, letters, "LoveLetter", "Read", icons[3])) {
			case 0:
				TextViewer(loveLetter, loveLetterLen, "03/16/2026", icons[3]);
				break;
			case 1:
				TextViewer(confessionLetter, confessionLetterLen, "02/09/2026", icons[3]);
				break;
			case 2:
				return;
				break;
		}
	}
}

void LoveBox() {
	int currentMessage = 0;

	while (true) {
		oled.clearDisplay();

		oled.setCursor(0, 0);
		oled.print(loveBox[currentMessage]);

		char bottomText[DISPLAY_MAX_CHAR-1];
		sprintf(bottomText, "marth#%d", currentMessage);
		drawBottomBar(bottomText, icons[4]);

		oled.display();

		if (handleButton("Exit")) {
			return;
		} else {
			currentMessage = currentMessage != loveBoxLen-1 ? currentMessage+1 : 0;
		}
	}
}

int hearts = 2;
void MovingHearts() {
	int
		x1 = (esp_random() % DISPLAY_WIDTH-16)+8,
		y1 = (esp_random() % DISPLAY_HEIGHT-16)+8,
		ax1 = 1,
		ay1 = 1,
		s1 = 1,
		x2 = (esp_random() % DISPLAY_WIDTH-16)+8,
		y2 = (esp_random() % DISPLAY_HEIGHT-16)+8,
		ax2 = -1,
		ay2 = -1,
		s2 = 1,
		x3 = (esp_random() % DISPLAY_WIDTH-16)+8,
		y3 = (esp_random() % DISPLAY_HEIGHT-16)+8,
		ax3 = -1,
		ay3 = 1,
		s3 = 1,
		x4 = (esp_random() % DISPLAY_WIDTH-16)+8,
		y4 = (esp_random() % DISPLAY_HEIGHT-16)+8,
		ax4 = 1,
		ay4 = -1,
		s4 = 1
	;

	while (true) {
		oled.clearDisplay();
		if (hearts >= 1) oled.drawBitmap(x1, y1, icons[4], 8, 8, 1);
		if (hearts >= 2) oled.drawBitmap(x2, y2, icons[4], 8, 8, 1);
		if (hearts >= 3) oled.drawBitmap(x3, y3, icons[4], 8, 8, 1);
		if (hearts == 4) oled.drawBitmap(x4, y4, icons[4], 8, 8, 1);
		oled.display();

		x1 += ax1*s1;
		y1 += ay1*s1;

		x2 += ax2*s2;
		y2 += ay2*s2;

		x3 += ax3*s3;
		y3 += ay3*s3;

		x4 += ax4*s4;
		y4 += ay4*s4;

		if (x1 < 0) x1 = 0;
		if (x1 > DISPLAY_WIDTH-8) x1 = DISPLAY_WIDTH-8;
		if (y1 < 0) y1 = 0;
		if (y1 > DISPLAY_HEIGHT-8) y1 = DISPLAY_HEIGHT-8;

		if (x2 < 0) x2 = 0;
		if (x2 > DISPLAY_WIDTH-8) x2 = DISPLAY_WIDTH-8;
		if (y2 < 0) y2 = 0;
		if (y2 > DISPLAY_HEIGHT-8) y2 = DISPLAY_HEIGHT-8;

		if (x3 < 0) x3 = 0;
		if (x3 > DISPLAY_WIDTH-8) x3 = DISPLAY_WIDTH-8;
		if (y3 < 0) y3 = 0;
		if (y3 > DISPLAY_HEIGHT-8) y3 = DISPLAY_HEIGHT-8;

		if (x4 < 0) x4 = 0;
		if (x4 > DISPLAY_WIDTH-8) x4 = DISPLAY_WIDTH-8;
		if (y4 < 0) y4 = 0;
		if (y4 > DISPLAY_HEIGHT-8) y4 = DISPLAY_HEIGHT-8;

		if (x1 >= DISPLAY_WIDTH-8 || x1 <= 0) {
			ax1 = -ax1;
			s1 = (esp_random() % 2)+1;
		}
		if (y1 >= DISPLAY_HEIGHT-8 || y1 <= 0) {
			ay1 = -ay1;
			s1 = (esp_random() % 2)+1;
		}

		if (x2 >= DISPLAY_WIDTH-8 || x2 <= 0) {
			ax2 = -ax2;
			s2 = (esp_random() % 2)+1;
		}
		if (y2 >= DISPLAY_HEIGHT-8 || y2 <= 0) {
			ay2 = -ay2;
			s2 = (esp_random() % 2)+1;
		}

		if (x3 >= DISPLAY_WIDTH-8 || x3 <= 0) {
			ax3 = -ax3;
			s3 = (esp_random() % 2)+1;
		}
		if (y3 >= DISPLAY_HEIGHT-8 || y3 <= 0) {
			ay3 = -ay3;
			s3 = (esp_random() % 2)+1;
		}

		if (x4 >= DISPLAY_WIDTH-8 || x4 <= 0) {
			ax4 = -ax4;
			s4 = (esp_random() % 2)+1;
		}
		if (y4 >= DISPLAY_HEIGHT-8 || y4 <= 0) {
			ay4 = -ay4;
			s4 = (esp_random() % 2)+1;
		}

		if (!digitalRead(BUTTON_PIN)) {return;}
		delay(16);
	}
}

void SetBrightness() {
	prefs.begin("settings", false);
	uint8_t brightness = prefs.getInt("brightness");
	while (true) {
		char bottomText[DISPLAY_MAX_CHAR+1];
		sprintf(bottomText, "Value: %d", brightness);
		drawBottomBar(bottomText, icons[0]);
		oled.display();
		if (handleButton("Set value")) {
			prefs.putInt("brightness", brightness);
			prefs.end();
			break;
		} else {
			brightness = brightness != 250 ? brightness+10 : 10;
			oled.ssd1306_command(SSD1306_SETCONTRAST);
			oled.ssd1306_command(brightness);
		}
	}
}

void SetHearts() {
	prefs.begin("settings", false);
	hearts = prefs.getInt("hearts");
	while (true) {
		char bottomText[DISPLAY_MAX_CHAR+1];
		sprintf(bottomText, "Value: %d", hearts);
		drawBottomBar(bottomText, icons[0]);
		oled.display();
		if (handleButton("Set value")) {
			prefs.putInt("hearts", hearts);
			prefs.end();
			break;
		} else {
			hearts = hearts != 4 ? hearts+1 : 1;
		}
	}
}

bool shelfmode = false;
void SetShelfMode() {
	prefs.begin("settings", false);
	shelfmode = prefs.getBool("shelfmode");

	char desc[84];
	sprintf(desc, "Are you sure you\nwant to turn %s\nShelf Mode?", shelfmode ? "off" : "on");
	if (!Dialog(desc, "Hold to toggle", "Toggle Shelf Mode", icons[7])) {prefs.end(); return;}

	prefs.putBool("shelfmode", !shelfmode);
	prefs.end();
}

void FactoryReset() {
	if (!Dialog("Are you sure you\nwant to start over?", "Hold to confirm", "Reset this device", icons[7])) return;

	prefs.begin("settings", false);
	prefs.clear();
	prefs.end();

	oled.clearDisplay();
	oled.setCursor(0, 0);
	oled.print("Restarting...");
	oled.display();

	delay(1000);
	ESP.restart();
}

void Settings() {
	const int TOTAL_SETTINGS = 5;
	const char settings[TOTAL_SETTINGS][DISPLAY_MAX_CHAR-1] = {
		"Brightness",
		"Visible Hearts",
		"Shelf Mode",
		"Factory Reset",
		"Back"
	};

	while (true) {
		switch (Menu(TOTAL_SETTINGS, settings, "Settings", "Set", icons[6])) {
			case 0:
				SetBrightness();	
				break;
			case 1:
				SetHearts();
				break;
			case 2:
				SetShelfMode();
				break;
			case 3:
				FactoryReset();
				break;
			case 4:
				return;
				break;
		}
	}
}

void About() {
	TextViewer(aboutText, aboutTextLen, "About this device", icons[7]);
}

// ----- STARTUP -----
void setup() {
	Serial.begin(115200);

	prefs.begin("settings", false);

	if (!prefs.isKey("brightness")) {
		prefs.putInt("brightness", 250);	
	}
	if (!prefs.isKey("hearts")) {
		prefs.putInt("hearts", 2);
	}
	if (!prefs.isKey("shelfmode")) {
		prefs.putBool("shelfmode", false);
	}
	if (!prefs.isKey("usedbefore")) {
		prefs.putBool("usedbefore", false);
	}

	shelfmode = prefs.getBool("shelfmode");
	hearts = prefs.getInt("hearts");

	pinMode(BUTTON_PIN, INPUT_PULLUP);

	Wire.begin(DISPLAY_DATA, DISPLAY_CLOCK);
	oled.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
	oled.setTextColor(SSD1306_WHITE);
	oled.ssd1306_command(SSD1306_SETCONTRAST);
	oled.ssd1306_command(prefs.getInt("brightness"));

	oled.clearDisplay();

	oled.setTextSize(2);
	oled.setCursor(DISPLAY_WIDTH/2-53,DISPLAY_HEIGHT/2-7);
	oled.print("LoveBoard");

	oled.display();

	delay(1000);

	for (int i = 0; i < 2; i++) {
		for (int p = -30; p <= DISPLAY_WIDTH; p = p+2) {
			oled.clearDisplay();

			oled.setTextSize(2);
			oled.setCursor(0, 0);
			oled.print("LoveBoxOS");
			oled.setTextSize(1);
			oled.setCursor(0, 16);
			if (DISPLAY_HEIGHT == 64) {
				oled.print("Mara's Edition");
			}

			if (p == -30 && i == 0) {oled.display(); delay(750);}

			oled.drawLine(p, DISPLAY_HEIGHT-10, p+30, DISPLAY_HEIGHT-10, 1);
			oled.setCursor(1, DISPLAY_HEIGHT-8);
			oled.print("Starting up...");

			oled.display();
		}
	}

	if (prefs.getBool("shelfmode")) MovingHearts();

	for (int p = DISPLAY_WIDTH; p > 0; p = p - 4) {
		oled.clearDisplay();

		oled.drawLine(p, DISPLAY_HEIGHT-10, DISPLAY_WIDTH-1, DISPLAY_HEIGHT-10, 1);

		oled.display();
	}

	if (!prefs.getBool("usedbefore")) {
		Tutorial();
		prefs.putBool("usedbefore", true);
		Dialog("You'll be redirected\nto \"LoveLetter\".", "OK", "OK", icons[3]);
		LoadingScreen("LoveLetter", icons[3]);
		TextViewer(loveLetter, loveLetterLen, "03/16/2026", icons[3]);
	}

	prefs.end();
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
			LoadingScreen("Tutorial", icons[2]);
			Tutorial();
			break;
		case 1:
			LoadingScreen("LoveLetter", icons[3]);
			LoveLetter();
			break;
		case 2:
			LoadingScreen("LoveBox", icons[4]);
			LoveBox();
			break;
		case 3:
			LoadingScreen("MovingHearts", icons[5]);
			MovingHearts();
			break;
		case 4:
			LoadingScreen("Settings", icons[6]);
			Settings();
			break;
		case 5:
			LoadingScreen("About", icons[7]);
			About();
			break;
	}

}
