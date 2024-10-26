#pragma once

#ifdef ARDUINO
#include <Arduino.h>

#else
#include <cstdint>

#endif

class CountDownTimer {
 public:
  CountDownTimer(uint32_t duration) : duration_(duration) {}

  void Reset() {
    started_ = true;
    started_at_ = millis();
    expires_ = started_at_ + duration_;
  }

  void Stop() { started_ = false; }

  bool Expired() {
    const uint32_t now = millis();
    if (!started_) {
      return false;
    }
    if (started_at_ > expires_) {
      return now < started_at_ && millis() > expires_;
    } else if (started_at_ > now) {
      return true;
    }
    return now > expires_;
  }

  bool Active() {
    const uint32_t now = millis();
    if (!started_) {
      return false;
    }
    if (started_at_ > expires_) {
      return now >= started_at_ || millis() <= expires_;
    } else if (started_at_ > now) {
      return false;
    }
    return now <= expires_;
  }

  bool Running() { return started_; }

 protected:
  const uint32_t duration_;
  uint32_t started_at_;
  uint32_t expires_ = 0;
  bool started_ = false;
};

class CountUpTimer {
 public:
  CountUpTimer() {}

  void Reset() {
    started_ = true;
    started_millis_ = millis();
  }

  void Stop() { started_ = false; }

  bool Running() { return started_; }

  uint32_t Get() {
    if (started_) {
      return millis() - started_millis_;
    } else {
      return 0;
    }
  }

 private:
  uint32_t started_millis_ = 0;
  bool started_ = false;
};
