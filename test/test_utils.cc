#include <gtest/gtest.h>
#include <hud/views/view.h>
#include <hud/utils.h>

TEST(TestUtils, BasicCases) {
  Rect start = {0, 0, 500, 500};
  Rect target = {0, 0, 1280, 720};
  Point p(500, 500);
  Point adapted = hud::utils::scaleToView(p, start, target);
  ASSERT_EQ(adapted.x, 1280.0);
  ASSERT_EQ(adapted.y, 720.0);

  Point adapted2 = hud::utils::scaleToView(Point(0, 0), start, target);
  ASSERT_EQ(adapted2.x, 0.0);
  ASSERT_EQ(adapted2.y, 0.0);

  Point adapted3 = hud::utils::scaleToView(Point(250, 250), start, target);
  ASSERT_EQ(adapted3.x, 640);
  ASSERT_EQ(adapted3.y, 360);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
