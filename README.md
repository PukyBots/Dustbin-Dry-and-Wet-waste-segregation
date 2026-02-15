# 🌱 Ultrasonic + Soil Moisture + Servo System (Arduino)

A simple Arduino project that integrates an **ultrasonic distance sensor**, **soil moisture sensor**, and **servo motor** to create an interactive system that reacts to obstacles and soil conditions.

---

## 🧠 Project Overview

This project detects obstacles using an **HC-SR04 ultrasonic sensor**.  
When an obstacle is detected within **30 cm**, the system waits for **3 seconds**, then checks the soil moisture using a **digital moisture sensor**:

- If the **soil is wet**, the servo motor turns to **0°** and returns to **90°**.  
- If the **soil is dry**, the servo motor turns to **180°** and returns to **90°**.  

All sensor readings and system actions are printed to the **Serial Monitor**.

---

## 🧩 Components Used

| Component | Quantity | Description |
|------------|-----------|-------------|
| Arduino UNO / Nano | 1 | Microcontroller board |
| HC-SR04 Ultrasonic Sensor | 1 | Distance measurement |
| Soil Moisture Sensor (Digital Output) | 1 | Detects wet/dry soil |
| Servo Motor (SG90 or similar) | 1 | Performs angle-based movement |
| Jumper Wires | — | Connections |
| Breadboard | 1 | Optional, for testing |
| Power Supply | 5V | Common for all components |

---

## ⚙️ Pin Connections

| Component | Arduino Pin | Description |
|------------|--------------|-------------|
| Ultrasonic TRIG | 9 | Trigger pin |
| Ultrasonic ECHO | 10 | Echo pin |
| Servo Signal | 8 | PWM control |
| Moisture Sensor (DO) | 7 | Digital output (HIGH = Dry, LOW = Wet) |
| 5V / GND | — | Common power lines |

> ⚠️ **Tip:** Use a separate 5V power supply for the servo motor if it draws too much current, but make sure to connect all **grounds (GND)** together.

---

## 🧾 Code Explanation

- **Ultrasonic Sensor:** Measures distance using sound pulse echo.
- **Soil Moisture Sensor:** Provides a HIGH signal when the soil is **dry**, and LOW when **wet**.
- **Servo Motor:** Rotates based on soil condition.
- **Serial Monitor:** Displays live readings and actions for easy debugging.

---

## 💻 Arduino Code

```cpp
#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define SERVO_PIN 8
#define MOISTURE_PIN 7

Servo myservo;

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOISTURE_PIN, INPUT);

  myservo.attach(SERVO_PIN);
  myservo.write(90);

  Serial.println("Ultrasonic + Moisture + Servo System Started...");
}

void loop() {
  float distance = getDistance();

  // Ignore invalid readings
  if (distance <= 0 || distance > 400) {
    Serial.println("No valid obstacle detected...");
    delay(300);
    return;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 30) {
    Serial.println("Obstacle detected! Waiting 3 seconds for soil sensor...");
    delay(3000);

    int moistureState = digitalRead(MOISTURE_PIN);

    if (moistureState == HIGH) {  // Dry soil
      Serial.println("Soil is DRY — Turning servo to 180°");
      myservo.write(180);
      delay(1000);
      myservo.write(90);
    } 
    else {  // Wet soil
      Serial.println("Soil is WET — Turning servo to 0°");
      myservo.write(0);
      delay(1000);
      myservo.write(90);
    }

    delay(1000);
  }

  delay(300);
}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 0;
  return duration * 0.034 / 2;
}
```

---


🧪 **How It Works**

The ultrasonic sensor continuously measures distance.

When an obstacle is detected closer than 30 cm, the system waits 3 seconds.

The soil moisture sensor checks the soil condition:

Wet Soil (LOW) → Servo turns 0°, returns to 90°.

Dry Soil (HIGH) → Servo turns 180°, returns to 90°.

System prints all results to the Serial Monitor.

---

📄 License

This project is open-source under the MIT License.
You are free to modify and use it for educational or personal projects.

---

👨‍💻 Author

Pulkit Garg
