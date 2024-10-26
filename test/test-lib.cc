#include "test-lib.h"

static uint32_t millis_ = 0;

uint32_t millis() { return millis_; }

void setMillis(uint32_t millis) { millis_ = millis; }

void advanceMillis(uint32_t millis) { millis_ += millis; }
