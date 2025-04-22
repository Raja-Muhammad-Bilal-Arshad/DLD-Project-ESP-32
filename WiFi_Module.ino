#include <WiFi.h>  // For ESP32 Wi-Fi

const char* ssid     = "Your_SSID";       // 🔁 Change this
const char* password = "Your_PASSWORD";   // 🔁 Change this

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("📶 Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
    delay(500);
    Serial.print(".");
    retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi connected!");
    Serial.print("📡 IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Failed to connect to Wi-Fi.");
  }
}

void loop() {
  // You can now do internet stuff here...
}
