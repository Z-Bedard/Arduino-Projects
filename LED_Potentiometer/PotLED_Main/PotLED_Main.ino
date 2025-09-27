// Fade an LED up/down using PWM (pin 9) with speed set by a pot on A0.

const int ledPin = 9;   // must be a PWM pin: 3,5,6,9,10,11 on Uno

void setup() {
  pinMode(ledPin, OUTPUT);
  // Optional: Serial.begin(9600);
}

void loop() {
  // Get value from potentiometer (Connected to A0)
  int pot = analogRead(A0);
  
  // Set brightness for LED (Remap the scale from one to the other)
  // In this case the binary value to an LED value
  int brightness = map(pot, 0, 1023, 0, 255);

  // Output to LED
  analogWrite(ledPin, brightness);
}
