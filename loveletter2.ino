#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const uint8_t BUTTON = 3;
bool BCURRENT = false;
bool BLAST = false;

const int lines = 6;
int index = 0;

const char message[lines][22] = {
	"nigga",
	"nigga",
	"nigga",
	"nigga",
	"nigga",
	"nigga"
};

void updateDisplay() {
	oled.clearDisplay();

	oled.setCursor(0, 0);
	int m = index+7 > lines ? lines : index+7;
	for (int i = index; i < m; i++) {
		oled.println(message[i]);
	}
	oled.drawLine(0, 54, 127, 54, 1);
	oled.setCursor(1, 56);
	oled.print(index+1); oled.print('/'); oled.println(lines);
	

	oled.display();
}

void setup() {
	pinMode(BUTTON, INPUT_PULLUP);

	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	oled.setTextColor(1);

	updateDisplay();
}

void loop() {
	BCURRENT = !digitalRead(BUTTON);

	if (BCURRENT != BLAST && BCURRENT == true) {

		long itime = millis();
		while (!digitalRead(BUTTON)) {if (millis() - itime == 200) {oled.fillRect(0, 54, 128, 10, 2); oled.display();}}
		if (millis() - itime < 200) {
			index = index != lines-1 ? index+1 : 0;
		} else {
			index = 0;nxtro

		}

		updateDisplay();

	}

	BLAST = BCURRENT;

	delay(40);
}
