// Pin Definitions
const int POT_PIN = 34; // Potentiometer connected to ADC1
const int LED_PIN = 4;  // PWM pin for LED control

// Serial print interval
unsigned long lastPrintTime = 0;
const unsigned long printInterval = 500; // Print every 500ms

void setup() {
  Serial.begin(115200);
  pinMode(POT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read the 12-bit raw analog value (0 - 4095)
  int potValue = analogRead(POT_PIN);

  // Map 12-bit ADC value (0-4095) to 8-bit PWM value (0-255)
  int brightness = map(potValue, 0, 4095, 0, 255);

  // Write PWM signal to control LED brightness in real-time
  analogWrite(LED_PIN, brightness);

  // Print values every 500ms
  if (millis() - lastPrintTime >= printInterval) {
    lastPrintTime = millis();

    Serial.print("Potentiometer Raw: ");
    Serial.print(potValue);
    Serial.print(" | LED PWM Brightness: ");
    Serial.print(brightness);
    Serial.print(" (");
    Serial.print((brightness / 255.0) * 100, 0);
    Serial.println("%)");
  }
}
