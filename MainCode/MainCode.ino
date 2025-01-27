// Define the pins for the HC-SR04 sensor, LED, and Buzzer
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 13;   // LED pin
const int buzzerPin = 7; // Buzzer pin

// Define motor control pins
const int in1 = 3;  // Left motor control
const int in2 = 4;  // Left motor control
const int in3 = 11;  // Right motor control
const int in4 = 12; // Right motor control

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  
  // Set the trigPin as an OUTPUT
  pinMode(trigPin, OUTPUT);
  
  // Set the echoPin as an INPUT
  pinMode(echoPin, INPUT);
  
  // Set the ledPin and buzzerPin as OUTPUT
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Set motor control pins as OUTPUT
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm
  float distance = (duration * 0.0343) / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Call the motor control function with the measured distance
  motorControl(distance);
  
  // Wait for a short period before the next measurement
  delay(100);
}

void motorControl(float distance) {
  // Randomly choose left or right turn
  int turnDirection = random(0, 2); // 0 for left, 1 for right

  if (distance < 10) {
    // Stop the car
    stopMotors();
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    delay(1000); // Wait for a second
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    // Reverse and turn randomly
    reverseMotors();
    delay(1000); // Reverse for a second
    if (turnDirection == 0) {
      turnLeft();
    } else {
      turnRight();
    }
    delay(1000); // Turn for a second
    stopMotors();
  } else if (distance >= 10 && distance < 20) {
    // Turn left or right randomly
    if (turnDirection == 0) {
      turnLeft();
    } else {
      turnRight();
    }
    // Turn on LED and Buzzer
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100); // Beep duration
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100); // Pause between beeps
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100); // Beep duration
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100); // Pause between beeps
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100); // Beep duration
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100); // Pause between beeps
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100); // Beep duration
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100); // Pause between beeps
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(100); // Beep duration
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    stopMotors();
  } else if (distance >= 20) {
    // Move forward
    digitalWrite(ledPin, HIGH); // Ensure LED is off when moving forward
    digitalWrite(buzzerPin, LOW); // Ensure Buzzer is off when moving forward
    moveForward();
  }
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Move Forward");
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  Serial.println("Stop Movement");
}

void reverseMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Reverse Movement");
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Turn Left");
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Turn Right");
}
