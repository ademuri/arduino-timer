// clang-format off
#include "test-lib.h"

#include "arduino-timer.h"
// clang-format on

#include <gtest/gtest.h>

#include <limits>

TEST(CountDownTimer, Simple) {
  setMillis(0);

  CountDownTimer timer{100};
  EXPECT_FALSE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_FALSE(timer.Running());

  timer.Reset();
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  setMillis(50);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  setMillis(100);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  setMillis(101);
  EXPECT_TRUE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_TRUE(timer.Running());

  setMillis(1000);
  EXPECT_TRUE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_TRUE(timer.Running());
}

TEST(CountDownTimer, MillisRollsOverDurationRollsOver) {
  setMillis(std::numeric_limits<uint32_t>::max() - 50);

  CountDownTimer timer{100};
  EXPECT_FALSE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_FALSE(timer.Running());

  timer.Reset();
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  advanceMillis(40);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  // 49 ms
  advanceMillis(9);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  // 50 ms
  advanceMillis(1);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  // 51 ms
  advanceMillis(1);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  // 99 ms
  advanceMillis(48);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  // 100 ms
  advanceMillis(1);
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  // 101 ms
  advanceMillis(1);
  EXPECT_TRUE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_TRUE(timer.Running());

  // 1101 ms
  advanceMillis(1000);
  EXPECT_TRUE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_TRUE(timer.Running());
}

TEST(CountDownTimer, MillisRollsOverDurationDoesNot) {
  setMillis(std::numeric_limits<uint32_t>::max() - 1000);

  CountDownTimer timer{100};
  EXPECT_FALSE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_FALSE(timer.Running());

  timer.Reset();
  EXPECT_FALSE(timer.Expired());
  EXPECT_TRUE(timer.Active());
  EXPECT_TRUE(timer.Running());

  advanceMillis(200);
  EXPECT_TRUE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_TRUE(timer.Running());

  advanceMillis(1000);
  EXPECT_TRUE(timer.Expired());
  EXPECT_FALSE(timer.Active());
  EXPECT_TRUE(timer.Running());
}

TEST(CountUpTimer, Simple) {
  setMillis(0);

  CountUpTimer timer;
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  setMillis(100);
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  timer.Reset();
  EXPECT_TRUE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  advanceMillis(100);
  EXPECT_TRUE(timer.Running());
  EXPECT_EQ(timer.Get(), 100);

  timer.Stop();
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  advanceMillis(100);
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);
}

TEST(CountUpTimer, MillisRollsOver) {
  setMillis(std::numeric_limits<uint32_t>::max() - 50);

  CountUpTimer timer;
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  setMillis(100);
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  timer.Reset();
  EXPECT_TRUE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  advanceMillis(100);
  EXPECT_TRUE(timer.Running());
  EXPECT_EQ(timer.Get(), 100);

  timer.Stop();
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);

  advanceMillis(100);
  EXPECT_FALSE(timer.Running());
  EXPECT_EQ(timer.Get(), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // if you plan to use GMock, replace the line above with
  // ::testing::InitGoogleMock(&argc, argv);

  if (RUN_ALL_TESTS())
    ;

  // Always return zero-code and allow PlatformIO to parse results
  return 0;
}
