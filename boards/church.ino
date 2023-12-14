int pins[] = {5, 4, 0, 2}; // Assign GPIO pins 0, 4, 2, and 5 on NodeMCU
int currentPin = 0; // Keeps track of the current pin
int delays[] = {1500, 1000, 500}; // Delay times for each state (in milliseconds)
int currentDelayIndex = 0; // Keeps track of the current delay index

void setup() {
  // Initialize GPIO pins as OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  int currentDelay = delays[currentDelayIndex];

  // Turn on the current pin
  digitalWrite(pins[currentPin], HIGH);

  // Delay for the specified time
  delay(currentDelay);

  // Turn off the current pin
  digitalWrite(pins[currentPin], LOW);

  // Increment the current pin index and delay index
  currentPin = (currentPin + 1) % 4;
  currentDelayIndex = (currentDelayIndex + 1) % 3;
}
