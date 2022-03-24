
const int PACKAGE_LENGTH = 2;

const int LEFT_IN_1_PIN = 2;
const int LEFT_IN_2_PIN = 4;
const int LEFT_PWM_PIN  = 5;

const int RIGHT_IN_1_PIN = 7;
const int RIGHT_IN_2_PIN = 8;
const int RIGHT_PWM_PIN  = 6;

const int TIMEOUT_MILIS = 500;

int JS_X;
int JS_Y;

int powerCurve(wheelInput) {
  return wheelInput;
}

void driveMotors(x, y) {
  int xSgn = (x >= 127) ? 1 : -1;
  int xMag = abs(x - 127);

  int ySgn = (y >= 127) ? 1 : -1;
  int yMag = abs(y - 127);

  int leftInput = ySgn * yMag - xSgn * xMag;
  int rightInput = -(ySgn * yMag) + xSgn * xMag;

  int leftPower = powerCurve(leftInput);
  int rightPower = powerCurve(rightInput);

  if(leftOutput >= 0) {
    digitalWrite(LEFT_IN_1_PIN, HIGH);
    digitalWrite(LEFT_IN_2_PIN, LOW);
  } else {
    digitalWrite(LEFT_IN_1_PIN, LOW);
    digitalWrite(LEFT_IN_2_PIN, HIGH);
  }

  if(rightOutput) {
    digitalWrite(RIGHT_IN_1_PIN, HIGH);
    digitalWrite(RIGHT_IN_2_PIN, LOW);
  } else {
    digitalWrite(RIGHT_IN_1_PIN, LOW);
    digitalWrite(RIGHT_IN_2_PIN, HIGH);
  }

  analogWrite(LEFT_PWM_PIN, leftPower);
  analogWrite(RIGHT_PWM_PIN, rightPower);
}


void setup() {
  pinMode(LEFT_IN_1_PIN, OUTPUT);
  pinMode(LEFT_IN_2_PIN, OUTPUT);
  pinMode(LEFT_PWM_PIN, OUTPUT);

  pinMode(RIGHT_IN_1_PIN, OUTPUT);
  pinMode(RIGHT_IN_2_PIN, OUTPUT);
  pinMode(RIGHT_PWM_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if(Serial.available() >= PACKAGE_LENGTH) {
    JS_X = Serial.read();
    JS_Y = Serial.read();
  }

  driveMotors(JS_X, JS_Y);
}
