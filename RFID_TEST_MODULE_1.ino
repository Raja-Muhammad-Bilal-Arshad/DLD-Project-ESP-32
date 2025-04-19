
//THIS SPECIFIC CODE PRINTS MY NAME AND MY ROLL NUMBER AS THE RFID READER GETS IN TOUCH OF MY CARD

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10     // GPIO10 (SS)
#define RST_PIN 9     // GPIO9 (reset pin)

MFRC522 rfid(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(9600);
  SPI.begin();       
  rfid.PCD_Init();   
  Serial.println("Scan your RFID card...");
}

void loop() {
  // Check for new RFID card
  if ( !rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial() )
    return;

  // Print your custom ID info
  Serial.println("Raja Muhammad Bilal Arshad");
  Serial.println("|24F-0787");
  Serial.println("------------------------");

  // Optional: halt card
  rfid.PICC_HaltA();
  delay(2000); // So it doesn't flood output
}
