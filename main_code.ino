// Ultrasonic Sensor Pins
#define TRIG_PIN 2  // Trigger pin connected to D2
#define ECHO_PIN 3  // Echo pin connected to D3

// Motor Control Pins
#define ENA 4  // PWM pin for left motors
#define IN1 5  // Direction pin 1 for left motors
#define IN2 6  // Direction pin 2 for left motors
#define ENB 7  // PWM pin for right motors
#define IN3 8  // Direction pin 1 for right motors
#define IN4 9  // Direction pin 2 for right motors

// Speed Constants (Adjusted for PWM range)
#define SPEED_FAST 255  // Max speed (for PWM)
#define SPEED_SLOW 128  // Slower speed (for PWM)
#define SPEED_STOP 0    // Stop speed

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Initialize ultrasonic sensor
    pinMode(TRIG_PIN, OUTPUT);  // Set TRIG_PIN as output
    pinMode(ECHO_PIN, INPUT);   // Set ECHO_PIN as input

    // Initialize motors
    pinMode(ENA, OUTPUT);  // PWM pin for left motors
    pinMode(IN1, OUTPUT);  // Direction pin 1 for left motors
    pinMode(IN2, OUTPUT);  // Direction pin 2 for left motors
    pinMode(ENB, OUTPUT);  // PWM pin for right motors
    pinMode(IN3, OUTPUT);  // Direction pin 1 for right motors
    pinMode(IN4, OUTPUT);  // Direction pin 2 for right motors

    randomSeed(millis());  // For randomness
}

float getDistance() {
    long duration;
    float distance;

    // Send a 10us HIGH pulse to trigger the sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure the time it takes for the echo to return
    duration = pulseIn(ECHO_PIN, HIGH);

    // Calculate distance in cm
    distance = duration * 0.034 / 2;

    // Print the distance to the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    return distance;  // Return the distance value
}

// Function to control the motors
void controlMotors(int leftSpeed, int rightSpeed, bool leftForward,
                   bool rightForward) {
    // Left motors
    digitalWrite(IN1, leftForward ? HIGH : LOW);
    digitalWrite(IN2, leftForward ? LOW : HIGH);
    analogWrite(ENA, abs(leftSpeed));

    // Right motors
    digitalWrite(IN3, rightForward ? HIGH : LOW);
    digitalWrite(IN4, rightForward ? LOW : HIGH);
    analogWrite(ENB, abs(rightSpeed));
}

// Move the car forward
void moveForward(int speed) { controlMotors(speed, speed, true, true); }

// Move the car backward
void moveBackward(int speed) { controlMotors(speed, speed, false, false); }

// Turn the car left
void turnLeft(int speed) { controlMotors(speed / 2, speed, true, true); }

// Turn the car right
void turnRight(int speed) { controlMotors(speed, speed / 2, true, true); }

// Stop the car
void stopMotors() { controlMotors(SPEED_STOP, SPEED_STOP, true, true); }

void motorControlLogic(float distance) {
    if (distance > 20) {
        moveForward(SPEED_FAST);  // No obstacle, move forward
    } else if (distance > 10 && distance <= 20) {
        stopMotors();
        delay(500);  // Brief stop
        if (random(2) == 0) {
            turnLeft(SPEED_FAST);  // Turn left
        } else {
            turnRight(SPEED_FAST);  // Turn right
        }
        delay(1000);  // Turning duration
    } else {
        // Close obstacle, slow down, stop, reverse, and steer
        moveForward(SPEED_SLOW);  // Slow forward
        delay(500);               // Allow slight movement
        stopMotors();
        delay(500);                // Pause
        moveBackward(SPEED_FAST);  // Move backward
        delay(1000);               // Reverse duration
        stopMotors();
        delay(500);  // Pause
        if (random(2) == 0) {
            turnLeft(SPEED_FAST);  // Steer left
        } else {
            turnRight(SPEED_FAST);  // Steer right
        }
        delay(1000);  // Steering duration
    }
}

void loop() {
    float distance = getDistance();
    motorControlLogic(distance);
}