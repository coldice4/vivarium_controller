int soil1_ADCPin = 34;
int soil2_ADCPin = 35;

void readSoilSensors() {
  doc["soil1"] = analogRead(soil1_ADCPin);
  doc["soil2"] = analogRead(soil2_ADCPin);
}
