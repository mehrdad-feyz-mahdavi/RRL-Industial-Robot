#define M1_PWM PB6
#define M1_DIR1 PB12
#define M1_DIR2 PB13
#define M2_PWM PB7
#define M2_DIR1 PB14
#define M2_DIR2 PB15
#define M3_PWM PB8
#define M3_DIR1 PA11
#define M3_DIR2 PA12
#define M4_PWM PB9
#define M4_DIR1 PB4
#define M4_DIR2 PB5

#define WHEEL_DIAMETER 15.0  // cm
#define WHEEL_RADIUS 0.075   // meters (7.5cm)
#define ENCODER_SLOTS 100
#define PI 3.141592653589793
#define SAMPLE_TIME 0.1  // seconds for RPM calculation
#define MAX_RPM 300      // Maximum expected RPM for scaling

volatile int encoderCount1 = 0;
volatile int encoderCount2 = 0;
volatile int encoderCount3 = 0;
volatile int encoderCount4 = 0;
volatile int lastEncoderCount1 = 0;
volatile int lastEncoderCount2 = 0;
volatile int lastEncoderCount3 = 0;
volatile int lastEncoderCount4 = 0;
volatile float rpm1 = 0, rpm2 = 0, rpm3 = 0, rpm4 = 0;
volatile unsigned long lastRpmTime = 0;

// PID and IMU Variables
double Kp = 3.0, Ki = 0.7, Kd = 1;
double targetAngle = 0.0;
double integral = 0.0, previousError = 0.0;
unsigned long lastPIDTime = 0;
int GY = 0;
unsigned long lastImuUpdate = 0;
int buff[8];
int counter;
String cmdBuffer = "";
bool readingMessage = false;
float target_rpm1 = 0, target_rpm2 = 0, target_rpm3 = 0, target_rpm4 = 0;
int pwm1 = 0, pwm2 = 0, pwm3 = 0, pwm4 = 0;

HardwareSerial IMU(USART2);
int m1 = 0, m2 = 0, m3 = 0, m4 = 0;

void setup() {
  pinMode(PC13, OUTPUT);
  pinMode(PC14, OUTPUT);
  digitalWrite(PC13, 1);
  digitalWrite(PC14, 1);
  pinMode(PB3, OUTPUT);
  digitalWrite(PB3, 1);

  // Initialize motor pins
  pinMode(M1_PWM, OUTPUT);
  pinMode(M1_DIR1, OUTPUT);
  pinMode(M1_DIR2, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(M2_DIR1, OUTPUT);
  pinMode(M2_DIR2, OUTPUT);
  pinMode(M3_PWM, OUTPUT);
  pinMode(M3_DIR1, OUTPUT);
  pinMode(M3_DIR2, OUTPUT);
  pinMode(M4_PWM, OUTPUT);
  pinMode(M4_DIR1, OUTPUT);
  pinMode(M4_DIR2, OUTPUT);

  // Encoder interrupts
  pinMode(PB1, INPUT_PULLUP);  // Encoder 1
  pinMode(PB0, INPUT_PULLUP);  // Encoder 2
  pinMode(PA7, INPUT_PULLUP);  // Encoder 3
  pinMode(PA6, INPUT_PULLUP);  // Encoder 4

  attachInterrupt(digitalPinToInterrupt(PB1), encoder1ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(PB0), encoder2ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(PA7), encoder3ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(PA6), encoder4ISR, RISING);

  // Serial for motors (USART1)
  Serial.setRx(PA10);
  Serial.setTx(PA9);
  Serial.begin(115200);

  IMU.setRx(PA3);
  IMU.setTx(PA2);
  IMU.begin(115200);

  // GY-25 initialization
  delay(500);
  IMU.write(0xA5);
  IMU.write(0x54);
  delay(500);
  IMU.write(0xA5);
  IMU.write(0x51);
  delay(500);
  IMU.write(0xA5);
  IMU.write(0x55);
  delay(500);

  digitalWrite(PC13, 0);
  digitalWrite(PC14, 0);
  lastRpmTime = millis();
}

double computePID(double input) {
  unsigned long now = millis();
  double dt = (now - lastPIDTime) / 1000.0;
  lastPIDTime = now;

  double error = targetAngle - input;
  integral += error * dt;
  double derivative = (error - previousError) / dt;
  previousError = error;

  integral = constrain(integral, -100.0, 100.0);
  return Kp * error + Ki * integral + Kd * derivative;
}

void loop() {
  // Calculate RPM for each motor
  if (millis() - lastRpmTime >= SAMPLE_TIME * 1000) {
    unsigned long timeElapsed = millis() - lastRpmTime;
    lastRpmTime = millis();

    // Calculate RPM for each wheel (counts per minute / counts per revolution)
    rpm1 = (encoderCount1 - lastEncoderCount1) * (60.0 / (ENCODER_SLOTS * timeElapsed / 1000.0));
    rpm2 = (encoderCount2 - lastEncoderCount2) * (60.0 / (ENCODER_SLOTS * timeElapsed / 1000.0));
    rpm3 = (encoderCount3 - lastEncoderCount3) * (60.0 / (ENCODER_SLOTS * timeElapsed / 1000.0));
    rpm4 = (encoderCount4 - lastEncoderCount4) * (60.0 / (ENCODER_SLOTS * timeElapsed / 1000.0));

    lastEncoderCount1 = encoderCount1;
    lastEncoderCount2 = encoderCount2;
    lastEncoderCount3 = encoderCount3;
    lastEncoderCount4 = encoderCount4;

    // Adjust PWM based on target RPM
    adjustMotorSpeed();
  }

  if (Serial.available() > 0) {
    digitalWrite(PC13, 1);
    char c = Serial.read();

    if (c == 'M' || c == 'S' || c == 'R' || c == 'V') {
      cmdBuffer = String(c);
      readingMessage = true;
    } else if (readingMessage) {
      cmdBuffer += c;
      if (c == 'E') {
        processMessage(cmdBuffer);
        cmdBuffer = "";
        readingMessage = false;
      }
    }
    digitalWrite(PC13, 0);
  }

  readIMU();

  double pidOutput = computePID(GY);
  int correction = constrain((int)pidOutput, -255, 255);

  setMotor(M1_PWM, M1_DIR1, M1_DIR2, pwm1 + correction);
  setMotor(M2_PWM, M2_DIR1, M2_DIR2, pwm2 + correction);
  setMotor(M3_PWM, M3_DIR1, M3_DIR2, pwm3 + correction);
  setMotor(M4_PWM, M4_DIR1, M4_DIR2, pwm4 + correction);
}

void adjustMotorSpeed() {
  // Simple P controller for RPM adjustment
  static const float Kp_rpm = 0.5;  // Proportional gain for RPM control

  // Calculate PWM based on target RPM (scale RPM to PWM)
  // pwm1 = constrain((target_rpm1 / MAX_RPM) * 255, -255, 255);
  // pwm2 = constrain((target_rpm2 / MAX_RPM) * 255, -255, 255);
  // pwm3 = constrain((target_rpm3 / MAX_RPM) * 255, -255, 255);
  // pwm4 = constrain((target_rpm4 / MAX_RPM) * 255, -255, 255);

  // Add RPM feedback correction
  float error1 = target_rpm1 - rpm1;
  pwm1 += Kp_rpm * error1;
  float error2 = target_rpm2 - rpm2;
  pwm2 += Kp_rpm * error2;
  float error3 = target_rpm3 - rpm3;
  pwm3 += Kp_rpm * error3;
  float error4 = target_rpm4 - rpm4;
  pwm4 += Kp_rpm * error4;

  // Constrain to valid PWM values
  pwm1 = constrain(pwm1, -255, 255);
  pwm2 = constrain(pwm2, -255, 255);
  pwm3 = constrain(pwm3, -255, 255);
  pwm4 = constrain(pwm4, -255, 255);
}

void processMessage(String cmd) {
  if (cmd.length() == 18 && cmd.startsWith("M") && cmd.endsWith("E")) {
    // Interpret values as RPM instead of direct PWM
    target_rpm1 = cmd.substring(2, 5).toInt() * (cmd[1] == '+' ? 1 : -1);
    target_rpm2 = cmd.substring(6, 9).toInt() * (cmd[5] == '+' ? 1 : -1);
    target_rpm3 = cmd.substring(10, 13).toInt() * (cmd[9] == '+' ? 1 : -1);
    target_rpm4 = cmd.substring(14, 17).toInt() * (cmd[13] == '+' ? 1 : -1);
  } else if (cmd.startsWith("S") && cmd.endsWith("E")) {
    targetAngle = cmd.substring(1, cmd.length() - 1).toDouble();
    targetAngle = constrain(targetAngle, 0.0, 180.0);
    integral = 0.0;  // Reset integral term
    previousError = 0.0;
  } else if (cmd.startsWith("R") && cmd.endsWith("E")) {
    Serial.print(encoderCount1 >= 0 ? '+' : '-');
    Serial.print(abs(encoderCount1));
    Serial.print(encoderCount2 >= 0 ? '+' : '-');
    Serial.print(abs(encoderCount2));
    Serial.print(encoderCount3 >= 0 ? '+' : '-');
    Serial.print(abs(encoderCount3));
    Serial.print(encoderCount4 >= 0 ? '+' : '-');
    Serial.print(abs(encoderCount4));
    Serial.println('E');
  } else if (cmd.startsWith("V") && cmd.endsWith("E")) {
    Serial.print(rpm1 >= 0 ? '+' : '-');
    Serial.print(abs(int(rpm1)));
    Serial.print(rpm2 >= 0 ? '+' : '-');
    Serial.print(abs(int(rpm2)));
    Serial.print(rpm3 >= 0 ? '+' : '-');
    Serial.print(abs(int(rpm3)));
    Serial.print(rpm4 >= 0 ? '+' : '-');
    Serial.print(abs(int(rpm4)));
    Serial.print('E');
  }
}

// ... [keep all remaining existing functions the same] ...
void readIMU() {
  IMU.write(0xA5);
  IMU.write(0x51);
  while (true) {
    buff[counter] = IMU.read();
    if (counter == 0 && buff[0] != 0xAA) break;
    counter++;
    if (counter == 8) {
      counter = 0;
      if (buff[0] == 0xAA && buff[7] == 0x55) {
        GY = (int16_t)(buff[1] << 8 | buff[2]) / 100.0;
      }
    }
  }
}

void setMotor( float pwm, float dir1, float dir2, float speed) {
  speed = constrain(speed, -255, 255);
  analogWrite(pwm, abs(speed));
  digitalWrite(dir1, speed > 0 ? HIGH : LOW);
  digitalWrite(dir2, speed > 0 ? LOW : HIGH);
}

// **Updated Encoder Interrupts**
void encoder1ISR() {
  digitalToggle(PC14);
  encoderCount1 += (pwm1 > 0) ? 1 : -1;
}

void encoder2ISR() {
  digitalToggle(PC14);
  encoderCount2 += (pwm2 > 0) ? 1 : -1;
}

void encoder3ISR() {
  digitalToggle(PC14);
  encoderCount3 += (pwm3 > 0) ? 1 : -1;
}

void encoder4ISR() {
  digitalToggle(PC14);
  encoderCount4 += (pwm4 > 0) ? 1 : -1;
}

// Convert encoder counts to wheel distance in cm
double getWheelDistance(int count) {
  double wheelCircumference = PI * WHEEL_DIAMETER;
  return (count / (double)ENCODER_SLOTS) * wheelCircumference;
}
