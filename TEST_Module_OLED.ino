#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Not used with I2C
#define SCREEN_ADDRESS 0x3C  // Try 0x3C if 0x78 doesn't work

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // Initialize I2C with your custom pins
  Wire.begin(8, 7); // SDA = GPIO8, SCL = GPIO7

  // Init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 OLED not found. Check wiring!"));
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("RAJA MUHAMMAD BILAL ARSHAD"));
  display.display();
}

void loop() {
  // You can refresh text here if needed
}
