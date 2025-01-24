// Define motor control pins
const int in1 = 3;  // Left motor control
const int in2 = 4;  // Left motor control
const int ena = 5;  // Left motor enable
const int in3 = 6;  // Right motor control
const int in4 = 11; // Right motor control
const int enb = 12; // Right motor enable

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  moveForward();
  Serial.print("Move Forward");
  delay(2000);
  reverseMotors();
  Serial.print("Move Backward");
  delay(2000);
  turnLeft();
  Serial.print("Move Left");
  delay(2000);
  turnRight();
  Serial.print("Move Right");
  delay(2000);
  stopMotors();
  delay(2000);
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 255); // Full speed
  analogWrite(enb, 255); // Full speed
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void reverseMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 255); // Full speed
  analogWrite(enb, 255); // Full speed
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, 127); // Half speed
  analogWrite(enb, 255); // Full speed
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ena, 255); // Full speed
  analogWrite(enb, 127); // Half speed
}
