// ADC Pin Definitions
const int POT_PIN = 34; // Potentiometer signal pin
const int LDR_PIN = 35; // LDR voltage divider signal pin

// Timing Variables
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 500; // 500 ms interval

void setup() {
  Serial.begin(115200);
  pinMode(POT_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastPrintTime >= printInterval) {
    lastPrintTime = currentMillis;

    // Read 12-bit raw values (0 - 4095)
    int potRaw = analogRead(POT_PIN);
    int ldrRaw = analogRead(LDR_PIN);

    // Convert raw ADC readings to voltages
    float potVolt = (potRaw / 4095.0) * 3.3;
    float ldrVolt = (ldrRaw / 4095.0) * 3.3;

    // Output to Serial Monitor
    Serial.print("POT -> Raw: ");
    Serial.print(potRaw);
    Serial.print(" (");
    Serial.print(potVolt, 2);
    Serial.print("V) | LDR -> Raw: ");
    Serial.print(ldrRaw);
    Serial.print(" (");
    Serial.print(ldrVolt, 2);
    Serial.println("V)");
  }
}
