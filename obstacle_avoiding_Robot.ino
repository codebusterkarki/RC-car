#define trigPin 11
#define echoPin 12

#define ENA 3
#define ENB 5
#define IN1 2
#define IN2 4
#define IN3 6
#define IN4 7

long duration;
int distance;

// ===================== ULTRASONIC FUNCTION =====================
int getDistance() {
  long total = 0;

  for (int i = 0; i < 3; i++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms

    if (duration == 0) {
      total += 400; // no obstacle detected
    } else {
      total += duration * 0.034 / 2;
    }

    delay(10);
  }

  return total / 3; // average
}

// ===================== MOTOR FUNCTIONS =====================
void moveForward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ===================== SETUP =====================
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

// ===================== MAIN LOOP =====================
void loop() {
  distance = getDistance();

  Serial.print("Front Distance: ");
  Serial.println(distance);

  if (distance > 20) {
    moveForward();
  } 
  else {
    stopRobot();
    delay(200);

    // Move slightly backward for safety
    moveBackward();
    delay(300);
    stopRobot();
    delay(200);

    // ===== CHECK LEFT =====
    turnLeft();
    delay(350);
    stopRobot();
    delay(200);

    int leftDist = getDistance();
    Serial.print("Left: ");
    Serial.println(leftDist);

    // Return to center
    turnRight();
    delay(350);
    stopRobot();
    delay(200);

    // ===== CHECK RIGHT =====
    turnRight();
    delay(350);
    stopRobot();
    delay(200);

    int rightDist = getDistance();
    Serial.print("Right: ");
    Serial.println(rightDist);

    // Return to center
    turnLeft();
    delay(350);
    stopRobot();
    delay(200);

    // ===== DECISION =====
    if (leftDist > rightDist) {
      turnLeft();
      delay(400);
    } else {
      turnRight();
      delay(400);
    }
  }
}


// #define trigPin 11
// #define echoPin 12

// #define ENA 3
// #define ENB 5
// #define IN1 2
// #define IN2 4
// #define IN3 6
// #define IN4 7

// long duration;
// int distance;

// // ===================== ULTRASONIC FUNCTION (EXTENDED RANGE) =====================
// int getDistance() {
//   long total = 0;

//   for (int i = 0; i < 2; i++) {  // Reduced from 3 to 2 for faster readings
//     digitalWrite(trigPin, LOW);
//     delayMicroseconds(2);

//     digitalWrite(trigPin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trigPin, LOW);

//     // INCREASED TIMEOUT: from 30000 to 60000 microseconds
//     // This allows detection up to ~5 meters
//     long duration = pulseIn(echoPin, HIGH, 60000);

//     if (duration == 0) {
//       total += 500;  // Increased from 400 to 500 (max range ~5m)
//     } else {
//       total += duration * 0.034 / 2;  // Speed of sound formula
//     }

//     delay(10);
//   }

//   return total / 2;  // Average of 2 readings
// }

// // ===================== MOTOR FUNCTIONS =====================
// void moveForward() {
//   analogWrite(ENA, 200);  // Increased speed for faster response
//   analogWrite(ENB, 200);
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
// }

// void moveBackward() {
//   analogWrite(ENA, 200);
//   analogWrite(ENB, 200);
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
// }

// void turnLeft() {
//   analogWrite(ENA, 200);
//   analogWrite(ENB, 200);
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
// }

// void turnRight() {
//   analogWrite(ENA, 200);
//   analogWrite(ENB, 200);
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
// }

// void stopRobot() {
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
// }

// // ===================== SETUP =====================
// void setup() {
//   pinMode(trigPin, OUTPUT);
//   pinMode(echoPin, INPUT);

//   pinMode(ENA, OUTPUT);
//   pinMode(ENB, OUTPUT);
//   pinMode(IN1, OUTPUT);
//   pinMode(IN2, OUTPUT);
//   pinMode(IN3, OUTPUT);
//   pinMode(IN4, OUTPUT);

//   Serial.begin(9600);
// }

// // ===================== MAIN LOOP =====================
// void loop() {
//   distance = getDistance();

//   Serial.print("Front Distance (cm): ");
//   Serial.println(distance);

//   if (distance > 1000) {  // 1000 cm = 10 meters (or max sensor range)
//     moveForward();
//   }
//   else {
//     stopRobot();
//     delay(200);

//     moveBackward();
//     delay(300);
//     stopRobot();
//     delay(200);

//     // Check left
//     turnLeft();
//     delay(350);
//     stopRobot();
//     delay(200);

//     int leftDist = getDistance();
//     Serial.print("Left: ");
//     Serial.println(leftDist);

//     turnRight();
//     delay(350);
//     stopRobot();
//     delay(200);

//     // Check right
//     turnRight();
//     delay(350);
//     stopRobot();
//     delay(200);

//     int rightDist = getDistance();
//     Serial.print("Right: ");
//     Serial.println(rightDist);

//     turnLeft();
//     delay(350);
//     stopRobot();
//     delay(200);

//     // Decision
//     if (leftDist > rightDist) {
//       turnLeft();
//       delay(400);
//     } else {
//       turnRight();
//       delay(400);
//     }
//   }
// }