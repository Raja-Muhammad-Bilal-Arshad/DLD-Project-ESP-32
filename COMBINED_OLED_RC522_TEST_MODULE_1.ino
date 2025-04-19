#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>

#define OLED_SDA 8
#define OLED_SCL 7

#define RST_PIN 9
#define SS_PIN 10

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);

  // OLED setup
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED failed"));
    while (true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Waiting for card...");
  display.display();

  // RC522 setup
  SPI.begin(); 
  rfid.PCD_Init();
  delay(1000);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Card UID: ");
  String uidStr = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidStr += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    uidStr += String(rfid.uid.uidByte[i], HEX);
  }
  Serial.println(uidStr);

  // Show Name on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Card Detected:");
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Raja Muhammad");
  display.setCursor(0, 35);
  display.println("Bilal Arshad");
  display.display();

  delay(3000);  // Show name for 3 seconds
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Waiting for card...");
  display.display();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
