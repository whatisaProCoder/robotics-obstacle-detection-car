// Define the pins for the HC-SR04 sensor and LED
const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 7;
const int buzzerPin = 8;

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  
  // Set the trigPin as an OUTPUT
  pinMode(trigPin, OUTPUT);
  
  // Set the echoPin as an INPUT
  pinMode(echoPin, INPUT);
  
  // Set the ledPin as an OUTPUT
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
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
  
  // Calculate the distance in cm (speed of sound is 34300 cm/s)
  // Distance = (duration / 2) * speed of sound
  // Since the sound travels to the object and back, we divide by 2
  float distance = (duration * 0.0343) / 2;
  
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Turn on the LED if the distance is less than 10 cm
  if (distance < 20) {
    digitalWrite(ledPin, HIGH); // Turn on LED
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
    digitalWrite(buzzerPin, LOW);
  }
  
  // Wait for a short period before the next measurement
  delay(500);
}