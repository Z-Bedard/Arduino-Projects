#include <LiquidCrystal.h>
const int LCDdelay = 0;
const int buzzer = 13;
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);
const int speed_raw = A0; //Potentiometer for speed will come from A0

void setup() {
  lcd_1.begin(16,2);
  lcd_1.print("LCD Ready");
  pinMode(8, INPUT_PULLUP); //Set pin 8 to be the tilt sensor
  Serial.begin(115200);
  Serial.println("Tilt sensor test ready");
}

void loop() {
  int state = digitalRead(8);

  // Calculate 'Speed' and output to display
  int speed_in = analogRead(speed_raw);
  float speed = 0.32 + (9.98 * speed_in / 1023.0);
  lcd_1.setCursor(0,0);
  lcd_1.print("Speed: Mach ");
  lcd_1.print(speed, 2);

  // Outputs based on value read from the tilt sensor
  if (state == LOW){
    Serial.println("Tilted");
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    tone(13, 200);
    lcd_1.setCursor(0,1);
    lcd_1.print("                ");
    lcd_1.setCursor(0,1);
    lcd_1.print("CORRECT ROLL");
  } else {
    Serial.println("Level");
    noTone(13);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    lcd_1.setCursor(0,1);
    lcd_1.print("                ");
    lcd_1.setCursor(0,1);
    lcd_1.print("Stable");
  }

  delay(500);
}
