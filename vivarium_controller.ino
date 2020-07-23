#include <ArduinoJson.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

const char* ssid     = "HomeNet"; // Your WiFi ssid
const char* password = "Sahara45"; //Your Wifi password

// Get this sccret key from the wia dashboard. It should start with `d_sk`
const char* device_secret_key = "your-device-secret-key";

// Wia API parameters
char* mqtt_broker = "10.0.0.236";
int mqtt_port = 1883;

WiFiClient wifi;
int status = WL_IDLE_STATUS;

PubSubClient mqtt_client(wifi);
StaticJsonDocument<200> doc;
char msg[100];


void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setup_wifi();
  mqtt_client.setServer(mqtt_broker, mqtt_port);
}

// Loop function runs continuously
void loop() {
  int start_time = millis();
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop();

  readSoilSensors();
  doc["alive_time_ms"] = millis();

  serializeJson(doc, msg);
  Serial.print("Publish message: ");
  Serial.println(msg);
  mqtt_client.publish("vivarium", msg);

  int end_time = millis();
  delay(5000 - (end_time - start_time)); // Do a loop every 5 seconds
}
