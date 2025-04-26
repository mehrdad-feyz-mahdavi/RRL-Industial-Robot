#include <Arduino.h>
#include <Servo.h>

// STM32F103 Robotic Arm Control with Potentiometer Feedback
// Controls 3 DC motors with 3 potentiometers as position feedback
// Uses simple proportional control to maintain setpoints

            // Define motor control pins
HardwareSerial WIFI(USART2);

#define MOTOR1_PWM PB9  
#define MOTOR1_IN1 PB5

#define MOTOR2_PWM PB7  
#define MOTOR2_IN1 PB3

#define MOTOR3_PWM PB8 
#define MOTOR3_IN1 PB4
#define GRIPPER_ROTATE_PIN PA9  // Rotation servo
#define GRIPPER_CLAW_PIN PA10    // Open/close servo
#define STEPPER_STEP_PIN PB15
#define STEPPER_DIR_PIN PB12
#define STEPPER_ENABLE_PIN PB14

// Define potentiometer pins (ADC inputs)
#define POT1_PIN PB0  // ADC1
#define POT2_PIN PB1  // ADC2
#define POT3_PIN PA7  // ADC3
#define STEPPER_STEPS_PER_REV 200  // Adjust for your stepper
#define STEPPER_DELAY 1000  // microseconds between steps

          // Servo parameters
#define GRIPPER_MIN 0     // Fully closed position
#define GRIPPER_MAX 360   // Fully open position
#define ROTATE_MIN 0      // Min rotation angle
#define ROTATE_MAX 270    // Max rotation angle
#define SERVO_MIN_PULSE 544  // Minimum pulse width in microseconds
#define SERVO_MAX_PULSE 2400 // Maximum pulse width in microseconds

          // Control parameters
#define DEADZONE 3  // Minimum error to take action (in ADC units)
#define MAX_PWM 255  // Maximum PWM value (0-255)
#define KP 2.0       // Proportional gain (adjust as needed)

        // Setpoints for each joint (0-1023)
int setpoint1 = 300;
int setpoint2 = 300;
int setpoint3 = 500;
int baseAngle = 0;       // Current base angle (0-180)
int gripperRotate = 90;  // Gripper rotation angle
int gripperOpen = 0;     // Gripper open/close position
Servo gripperRotateServo;
Servo gripperClawServo;  // Add Servo object for claw

#define CLAW_PWM_MIN 500         // Minimum PWM pulse width (0.5ms) - adjusted for full close
#define CLAW_PWM_MAX 2500        // Maximum PWM pulse width (2.5ms) - adjusted for full open
#define CLAW_PWM_RANGE (CLAW_PWM_MAX - CLAW_PWM_MIN)
#define SERVO_REFRESH_RATE 20    // Standard servo refresh rate in ms

int last_time = 0;
void setup() {

  //Serial.setRx(PA10);
  //Serial.setTx(PA9);  // Initialize Serial communication
  WIFI.begin(115200);

  // Set motor control pins as outputs
  pinMode(MOTOR1_PWM, OUTPUT);
  pinMode(MOTOR1_IN1, OUTPUT);

  pinMode(MOTOR2_PWM, OUTPUT);
  pinMode(MOTOR2_IN1, OUTPUT);

  pinMode(MOTOR3_PWM, OUTPUT);
  pinMode(MOTOR3_IN1, OUTPUT);
          // Initialize potentiometers
  pinMode(POT1_PIN, INPUT);
  pinMode(POT2_PIN, INPUT);
  pinMode(POT3_PIN, INPUT);
        // Initialize stepper motor

  pinMode(STEPPER_STEP_PIN, OUTPUT);
  pinMode(STEPPER_DIR_PIN, OUTPUT);
  pinMode(STEPPER_ENABLE_PIN, OUTPUT);
  digitalWrite(STEPPER_ENABLE_PIN, HIGH);  // Enable stepper


          // Initialize servos
  gripperRotateServo.attach(GRIPPER_ROTATE_PIN);
  gripperClawServo.attach(GRIPPER_CLAW_PIN);
  
  // Set initial positions
  gripperRotate = 90;  // Center position
  gripperOpen = 0;     // Closed position
  updateServos();

          // Stop all motors initially
  controlMotor(1, 0);
  controlMotor(2, 0);
  controlMotor(3, 0);
  // Initialize ADC
  // analogReadResolution(10); // Set ADC to 10-bit resolution (0-1023)
}

void loop() {

        // Handle incoming WIFI commands
  if (WIFI.available()) {
    String cmd = WIFI.readStringUntil('E');
    
    if (cmd.startsWith("J1")) {  // Joint 1 command
      setpoint1 = cmd.substring(2).toInt();
    } 
    else if (cmd.startsWith("J2")) {  // Joint 2 command
      setpoint2 = cmd.substring(2).toInt();
    }
    else if (cmd.startsWith("J3")) {  // Joint 3 command
      setpoint3 = cmd.substring(2).toInt();
    }
    else if (cmd.startsWith("A")) {  // All joints command
      setpoint1 = cmd.substring(1,5).toInt();
      setpoint2 = cmd.substring(5,9).toInt();
      setpoint3 = cmd.substring(9).toInt();
    }
    else if (cmd.startsWith("B")) {  // Base rotation command
      int targetAngle = cmd.substring(1).toInt();
      rotateBase(targetAngle);
      WIFI.print("ACK B");
      WIFI.print(baseAngle);
      WIFI.println("E");
    }
    else if (cmd.startsWith("GR")) {  // Gripper rotation
      gripperRotate = cmd.substring(2).toInt();
      gripperRotate = constrain(gripperRotate, ROTATE_MIN, ROTATE_MAX);
      updateServos();
      WIFI.print("ACK GR");
      WIFI.print(gripperRotate);
      WIFI.println("E");
    }
     else if (cmd.startsWith("GC")) {  // Gripper claw
      gripperOpen = cmd.substring(2).toInt();
      gripperOpen = constrain(gripperOpen, GRIPPER_MIN, GRIPPER_MAX);
      updateServos();
      WIFI.print("ACK GC");
      WIFI.print(gripperOpen);
      WIFI.println("E");
    }
  }

  // Read current positions
  int current1 = analogRead(POT1_PIN);
  int current2 = analogRead(POT2_PIN);
  int current3 = analogRead(POT3_PIN);

  // Calculate errors
  int error1 = current1 - setpoint1;
  int error2 = (current2 - setpoint2);
  int error3 = (current3 - setpoint3);
  // Control motor 1
  controlMotor(1, error1);
  //Control motor 2
  controlMotor(2, error2);
  // Control motor 3
  controlMotor(3, error3);

  
}

void controlMotor(int motorNum, int error) {
  // Calculate proportional control signal
  int controlSignal = abs(error) > DEADZONE ? (int)(KP * error) : 0;

  // Constrain the control signal to PWM range
  controlSignal = constrain(controlSignal, -MAX_PWM, MAX_PWM);

  // Determine motor direction and PWM value
  int pwm = controlSignal;
  bool dir = controlSignal > 0;

  // Apply control to the appropriate motor
  switch (motorNum) {
    case 1:
      if (pwm > 0) {
        digitalWrite(MOTOR1_IN1, 0);
        analogWrite(MOTOR1_PWM, pwm);
      } else {
        digitalWrite(MOTOR1_IN1, 1);
        analogWrite(MOTOR1_PWM, 255 + pwm);
      }
      break;
    case 2:
      if (pwm > 0) {
        digitalWrite(MOTOR2_IN1, 0);
        analogWrite(MOTOR2_PWM, pwm);
      } else {
        digitalWrite(MOTOR2_IN1, 1);
        analogWrite(MOTOR2_PWM, 255 + pwm);
      }
      break;
    case 3:
      pwm = -pwm;
      if (pwm > 0) {
        digitalWrite(MOTOR3_IN1, 0);
        analogWrite(MOTOR3_PWM, pwm);
      } else {
        digitalWrite(MOTOR3_IN1, 1);
        analogWrite(MOTOR3_PWM, 255 + pwm);
      }
      break;
  }
}

void rotateBase(int targetAngle) {
  targetAngle = constrain(targetAngle, 0, 180);
  int stepsNeeded = (targetAngle - baseAngle) * STEPPER_STEPS_PER_REV / 180;
  
  // Enable the stepper motor
  digitalWrite(STEPPER_ENABLE_PIN, LOW);
  
  // Set direction
  digitalWrite(STEPPER_DIR_PIN, stepsNeeded > 0 ? HIGH : LOW);

  // Move the required number of steps
  for (int i = 0; i < abs(stepsNeeded); i++) {
    digitalWrite(STEPPER_STEP_PIN, HIGH);
    delayMicroseconds(STEPPER_DELAY);
    digitalWrite(STEPPER_STEP_PIN, LOW);
    delayMicroseconds(STEPPER_DELAY);
  }
  
  // Disable the stepper motor after movement is complete
  digitalWrite(STEPPER_ENABLE_PIN, HIGH);
  
  baseAngle = targetAngle;
}

void updateServos() {
  // Update rotation servo
  gripperRotate = constrain(gripperRotate, ROTATE_MIN, ROTATE_MAX);
  gripperRotateServo.write(gripperRotate);
  
  // Update claw servo using Servo library
  gripperOpen = constrain(gripperOpen, GRIPPER_MIN, GRIPPER_MAX);
  gripperClawServo.write(gripperOpen);
  
  // Add a small delay to ensure servo has time to move
  delay(15);
}

// Function to set new setpoints (call this from WIFI or other input)
void setSetpoints(int sp1, int sp2, int sp3) {
  setpoint1 = constrain(sp1, 0, 1023);
  setpoint2 = constrain(sp2, 0, 1023);
  setpoint3 = constrain(sp3, 0, 1023);
}
