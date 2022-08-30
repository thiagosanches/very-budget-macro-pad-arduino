#include <HID-Project.h>
#include <HID-Settings.h>

const int encoder0PinA = 3;
const int encoder0PinB = 8;
const int pinButton1 = 5;
const int pinButton2 = 7;

int val;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
long encoderLastValue = 0;
int lastDirection;
int n = LOW;

void setup() {
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(pinButton1, INPUT);
  pinMode(pinButton2, INPUT);

  Consumer.begin();
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(pinButton1) == HIGH) {
    Consumer.write(MEDIA_NEXT);
    delay(500);
  }
  
  if (digitalRead(pinButton2) == HIGH) {
    Consumer.write(MEDIA_PLAY_PAUSE);
    delay(500);
  }

  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      if (lastDirection == 0) {
        encoder0Pos--;
      }
      lastDirection = 0;
    } else {
      if (lastDirection == 1) {
        encoder0Pos++;
      }
      lastDirection = 1;
    }
  }
  encoder0PinALast = n;
  if (encoderLastValue > encoder0Pos) {
    Consumer.write(MEDIA_VOLUME_DOWN);
  }
  else if (encoderLastValue < encoder0Pos) {
    Consumer.write(MEDIA_VOLUME_UP);
  }
  encoderLastValue = encoder0Pos;
}
