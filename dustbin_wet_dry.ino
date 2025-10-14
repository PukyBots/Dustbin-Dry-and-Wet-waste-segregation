#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 8
#define MOISTURE_PIN 7   // Digital pin from soil moisture sensor

Servo myservo;

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOISTURE_PIN, INPUT);

  myservo.attach(SERVO_PIN);
  myservo.write(90);  // Neutral position

  Serial.println("Ultrasonic + Moisture + Servo System Started...");
}

void loop() {
  float distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 30) {
    Serial.println("Obstacle detected! Checking soil moisture...");
    delay(3000);
    int moistureState = digitalRead(MOISTURE_PIN);

    if (moistureState == HIGH) {  // Dry soil
      Serial.println("Soil is DRY — Turning servo to 180°");
      myservo.write(180);
      delay(1000);
      myservo.write(90);  // Return to center
    } 
    else {  // Wet soil
      Serial.println("Soil is WET — Turning servo to 0°");
      myservo.write(0);
      delay(1000);
      myservo.write(90);  // Return to center
    }

    delay(1000);  // Wait a bit before next reading
  }

  delay(300);
}

// --- FUNCTION TO MEASURE DISTANCE ---
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // convert to cm
}
