
const int LED_POWER_PIN = 9;

const int USER1_PIN = 14;
const int USER2_PIN = 16;

const int JS_X_PIN = 0; // analog
const int JS_Y_PIN = 1; // analog

const int PACKAGE_LENGTH = 2;


void setup() {
  Serial.begin(9600);
  pinMode(LED_POWER_PIN, OUTPUT);
}

void loop() {

  byte dataPackage[PACKAGE_LENGTH] = [analogRead(JS_X_PIN) >> 2, analogRead(JS_Y_PIN) >> 2]
  // [JS_X, JS_Y]

  Serial.write(dataPackage, PACKAGE_LENGTH)

  delay(200);
}
