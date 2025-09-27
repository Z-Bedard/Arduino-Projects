int ledPin = 13; //Pin 13 is linked to the LED we want

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT); //Set the mode of pin 13 to be an output
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, HIGH); //Turn on the LED by setting the pin to HIGH
  delay(1000); //All delays are in milliseconds so here is our 1 second delay
  digitalWrite(ledPin, LOW); //Turn off LED (pin to low)
  delay(1000);
}
