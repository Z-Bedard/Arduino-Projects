// Arduino Uno Telemetry Simulator (NDJSON over Serial)
// Sends one JSON object per line at ~10 Hz.
#include <LiquidCrystal.h>

const char* DEVICE_ID = "uno1";
const int POT_PIN   = A0;          // analog input for potentiometer (0..1023)
const unsigned long SAMPLE_PERIOD_MS = 100; // 10 kHz
const int LCDdelay = 0;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

unsigned long lastSampleMs = 0;

void setup() {
  lcd_1.begin(16,2); //Initialize the LCD screen
  lcd_1.print("LCD Ready");
  Serial.begin(115200);
  // Small delay so Serial Monitor/host can attach
  delay(500);
}

void loop() {
  unsigned long now = millis();
  if (now - lastSampleMs < SAMPLE_PERIOD_MS) return;
  lastSampleMs = now;

  // Read raw analog from pin A0 (0..1023)
  int potRaw = analogRead(POT_PIN);

  // Derive some simulated values values:
  // Map pot to a pretend temperature between 20.00°C and 100.00°C
  float tempC = 20.0 + (80.0 * potRaw / 1023.0);

  // Simulate battery voltage that slowly “breathes” between 4.85–4.95V
  // (simple triangle wave based on time)
  float phase = (now % 5000UL) / 5000.0; // 0..1 over 5 seconds
  float battV = 4.85 + (phase < 0.5 ? (phase * 0.2) : ((1.0 - phase) * 0.2));

  // NOTE: Build JSON with Serial.print pieces (don’t use printf %f on AVR).
  Serial.print("{");

  Serial.print("\"device_id\":\"");  // quotes around key and value
  Serial.print(DEVICE_ID);
  Serial.print("\",");

  Serial.print("\"ts_ms\":");
  Serial.print(now);
  Serial.print(",");

  Serial.print("\"temp_c\":");
  Serial.print(tempC, 2);
  Serial.print(",");

  Serial.print("\"batt_v\":");
  Serial.print(battV, 2);
  Serial.print(",");

  Serial.print("\"pot_raw\":");
  Serial.print(potRaw);

  Serial.println("}"); //This creates the new line in JSON
  //Output values to the LCD screen
  lcd_1.setCursor(0, 0); // Top row (Set where it starts)
  lcd_1.print("Temp: "); // Title for temp
  lcd_1.print(tempC, 2); // Output temp to two decimal places

  lcd_1.setCursor(0, 1); // Same Idea but start on the second row
  lcd_1.print("Volt: ");
  lcd_1.print(battV, 2);

}
