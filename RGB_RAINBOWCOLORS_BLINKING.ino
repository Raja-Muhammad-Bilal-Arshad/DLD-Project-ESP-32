#include <Adafruit_NeoPixel.h>

#define RGB_PIN     48     // Your RGB Data Pin
#define NUM_PIXELS  1      // Only 1 LED (onboard)
#define BRIGHTNESS  50     // Set to 0~255

Adafruit_NeoPixel strip(NUM_PIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Turn off all LEDs
}

void loop() {
  rainbowCycle(5); // Speed: lower = faster
}

// Function to loop through rainbow colors
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j = 0; j < 256; j++) { // 1 cycle of all colors
    for(i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i * 1 + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Generate rainbow colors across 0–255
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
