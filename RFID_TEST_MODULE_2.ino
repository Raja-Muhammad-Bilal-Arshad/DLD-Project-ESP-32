#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>

#define SS_PIN     10    // RFID SS (GPIO10)
#define RST_PIN    9     // RFID RST (GPIO9)
#define RGB_PIN    48    // RGB LED pin
#define NUM_PIXELS 1     // Only 1 RGB LED
#define BRIGHTNESS 50    // LED brightness

MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_NeoPixel strip(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  SPI.begin();             
  rfid.PCD_Init();         
  Serial.println("Scan your RFID card...");

  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.setPixelColor(0, strip.Color(0, 0, 0)); // Turn off LED
  strip.show();
}

void loop() {
  // Check for new RFID card
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Print your custom ID info
  Serial.println("Raja Muhammad Bilal Arshad");
  Serial.println("|24F-0787");
  Serial.println("------------------------");

  // Turn RGB LED GREEN
  strip.setPixelColor(0, strip.Color(0, 255, 0)); // R, G, B → GREEN
  strip.show();

  // Optional: Halt card so it doesn't keep re-triggering
  rfid.PICC_HaltA();
  delay(2000); // Delay to avoid spamming the scan
}
