#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const uint8_t BUTTON = 3;
bool BCURRENT = false;
bool BLAST = false;

const int lines = 8;
int index = 0;

const char message[lines][22] = {
	"Lorem ipsum dolor sit",
	"amet, consectetur",
	"adipiscing elit. Sed",
	"do eiusmod tempor",
	"incididunt ut labore"
	"et dolore magna",
	"aliqua. Ut enim ad",
	"minim veniam, quis"
};

void setup() {
	pinMode(BUTTON, INPUT_PULLUP);

	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	oled.clearDisplay();
	oled.setCursor(0, 0);
	oled.setTextColor(1);
	for (int i = 0; i < lines; i++) {
		oled.println(message[i]);
	}
	oled.display();
}

void loop() {
	BCURRENT = !digitalRead(BUTTON);

	if (BCURRENT != BLAST && BCURRENT == true) {
		if (index != lines-2) {
			index++;
		} else {
			index = 0;
		}
		oled.clearDisplay();
		oled.setCursor(0, 0);
		oled.print(index+1);
		oled.print('/');
		oled.println(lines);
		for (int i = 0+index; i < lines; i++) {
			oled.println(message[i]);
		}
		oled.display();
	}

	BLAST = BCURRENT;
}
