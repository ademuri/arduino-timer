// clang-format off
#include "test-lib.h"

#include "arduino-timer.h"
// clang-format on

#include <gtest/gtest.h>

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // if you plan to use GMock, replace the line above with
  // ::testing::InitGoogleMock(&argc, argv);

  if (RUN_ALL_TESTS())
    ;

  // Always return zero-code and allow PlatformIO to parse results
  return 0;
}
