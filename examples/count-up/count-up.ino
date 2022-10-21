#include "arduino-timer.h"

constexpr int kButton = 1;

CountUpTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(kButton, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(kButton)) {
    if (timer.Running()) {
      Serial.println(timer.Get());
      timer.Stop();
    } else {
      Serial.print("Starting timer... ");
      timer.Reset();
    }
  }
}
