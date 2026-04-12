#include <Joystick.h>

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_GAMEPAD,
  10,
  0,
  true, true,
  false,
  true, true,
  false, false, false, false, false
);

#define L_STICK_X A1
#define L_STICK_Y A0
#define R_STICK_X A3
#define R_STICK_Y A2

#define BTN_A 8
#define BTN_B 9
#define BTN_X 6
#define BTN_Y 7
#define DPAD_DOWN 3
#define DPAD_UP 4
#define DPAD_LEFT 2
#define DPAD_RIGHT 5
#define BTN_L 10
#define BTN_R 16

const int buttonPins[] = {
  BTN_A, BTN_B, BTN_X, BTN_Y, DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT, BTN_L, BTN_R
};
const int buttonCount = 10;

#define DEADZONE 20

int processAxis(int raw) {
  int centered = raw - 512;
  if (abs(centered) < DEADZONE) return 0;
  return centered;
}


void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < buttonCount; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  
  Joystick.setXAxisRange(-512, 512);
  Joystick.setYAxisRange(-512, 512);
  Joystick.setRxAxisRange(-512, 512);
  Joystick.setRyAxisRange(-512, 512);

  Joystick.begin(false);

}

void loop() {

  Joystick.setXAxisRange(processAxis(analogRead(L_STICK_X)));
  Joystick.setYAxisRange(processAxis(analogRead(L_STICK_Y)));
  Joystick.setRxAxisRange(processAxis(analogRead(R_STICK_X)));
  Joystick.setRyAxisRange(processAxis(analogRead(R_STICK_Y)));

  for (int i = 0; i < buttonCount; i++) {
    Joystick.setButton(i, !digitRead(buttonPins[i]));
  }

  Joystick.sendState();

  delay(10);
}
