#include <ArduinoJson.h>
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <Arduino.h>
#include <PubSubClient.h>

const char* ssid     = "HomeNet"; // Your WiFi ssid
const char* password = "Sahara45"; //Your Wifi password

IPAddress ip(10,0,0,237);
IPAddress gateway(10,0,0,1);
IPAddress subnet(10,0,0,0);
IPAddress dns1(10,0,0,1);
IPAddress dns2(8,8,8,8);

// Get this sccret key from the wia dashboard. It should start with `d_sk`
const char* device_secret_key = "your-device-secret-key";

// Wia API parameters
char* mqtt_broker = "10.0.0.236";
int mqtt_port = 1883;

WiFiClient wifi;
int status = WL_IDLE_STATUS;

PubSubClient mqtt_client(wifi);
char msg[50];


void setup() {
  // initialize serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setup_wifi();
  mqtt_client.setServer(mqtt_broker, mqtt_port);
}

void setup_wifi() {
  delay(10);
  //WiFi.config(ip, gateway, subnet, dns1, dns2);
  WiFi.begin(ssid, password);
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  // attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Connect to WPA/WPA2 network. 
    // wait 5 seconds for connection:
    delay(500);
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!mqtt_client.connected()) {
    Serial.print("Reconnecting...");
    if (!mqtt_client.connect("ESP8266Client")) {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" retrying in 5 seconds");
      delay(5000);
    }
  }
}

// Loop function runs continuously
void loop() {
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop();

  snprintf (msg, 50, "Alive since %ld milliseconds", millis());
  Serial.print("Publish message: ");
  Serial.println(msg);
  mqtt_client.publish("terrarium", msg);

  delay(3000); // Wait for 3 seconds to post again
}
