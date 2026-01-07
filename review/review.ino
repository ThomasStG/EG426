#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_ADDRESS 0x3C
#define OLED_RESET -1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define MotorPWM_A 4  //left motor
#define MotorPWM_B 5  //right motor

#define INA1A 32
#define INA2A 34
#define INA1B 30
#define INA2B 36

int count_left = 0;
int count_right = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/***************************************/
// This is the Interrupt Service Routine
// for the left motor.
/***************************************/
void ISRMotorLeft() {
  count_left++;
}

void ISRMotorRight() {
  count_right++;
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  pinMode(MotorPWM_A, OUTPUT);
  pinMode(MotorPWM_B, OUTPUT);
  pinMode(INA1A, OUTPUT);
  pinMode(INA2A, OUTPUT);
  pinMode(INA1B, OUTPUT);
  pinMode(INA2B, OUTPUT);
  pinMode(LEFT_ENCODER_FRONT, INPUT_PULLUP);
  pinMode(RIGHT_ENCODER_FRONT, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_FRONT), ISRMotorLeft, FALLING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_FRONT), ISRMotorRight, FALLING);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void loop() {
  display.display();
}
