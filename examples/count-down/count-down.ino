#include "arduino-timer.h"

const uint8_t kLedPin = 13;

// Create a timer with a 1-second period
CountDownTimer timer1{1000};

CountDownTimer timer2{2000};
CountDownTimer startup_timer{3000};

void setup() {
  Serial.begin(115200);
  pinMode(kLedPin, OUTPUT);

  startup_timer.Reset();
  bool on = true;
  do {
    digitalWrite(kLedPin, on);
    on = !on;
    delay(100);
    // Active returns true if the timer is running and not expired
  } while (startup_timer.Active());

  // Reset the timer to 0 and start it running. Note that timers are created
  // not-started.
  timer1.Reset();
  digitalWrite(kLedPin, HIGH);
}

void loop() {
  if (timer1.Running()) {
    if (timer1.Expired()) {
      digitalWrite(kLedPin, LOW);
      timer1.Stop();
      timer2.Reset();
    }
  } else {
    // !timer1.Running()
    if (timer2.Expired()) {
      digitalWrite(kLedPin, HIGH);
      timer2.Stop();
      timer1.Reset();
    }
  }
}
