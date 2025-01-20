#include <gtest/gtest.h>

TEST(SimpleTest, BasicAssertions) {
  EXPECT_EQ(2+2, 4);
  EXPECT_NE(5,3);
}
