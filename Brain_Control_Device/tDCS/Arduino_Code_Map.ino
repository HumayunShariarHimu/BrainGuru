int currentPin = 9;    // Define the output pin for current
int switchPin = 2;     // Switch pin for turning on/off

void setup() {
  pinMode(currentPin, OUTPUT); 
  pinMode(switchPin, INPUT_PULLUP);   // Set the switch as input
}

void loop() {
  if (digitalRead(switchPin) == LOW) {   // When switch is pressed
    analogWrite(currentPin, 128);         // Generate the current (1-255 scale)
  } else {
    analogWrite(currentPin, 0);           // No current
  }
}