# Arduino Timer

Count up and count down timers for use with Arduino.

Provides a more readable alternative to managing state with time variables. For example, without this library, you might write:

```c++
uint32_t print_at = 0;
constexpr uint32_t kPrintEvery = 5000;

void loop() {
  if (millis() > print_at) {
    Serial.println(millis());
    print_at = millis() + kPrintEvery;
  }
}
```

With a `CountDown` timer, you can instead write:

```c++
#include "arduino-timer.h"

CountDownTimer print_timer{5000};

void loop() {
  if (print_timer.Expired()) {
    Serial.println(millis());
    print_timer.Reset();
  }
}
```

See also the examples.
