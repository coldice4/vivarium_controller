void setup_wifi() {
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

  Serial.println();
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
    Serial.println();
  }
}
