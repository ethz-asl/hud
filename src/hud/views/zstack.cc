#include <hud/views/zstack.h>
#include <iostream>

namespace hud::views {

ZStack::ZStack() : StackView() {}

ZStack::ZStack(const std::function<void(LayoutContext*)> &fn) : StackView() {
  LayoutContext layout;
  fn(&layout);
  child_views = layout.views;
}

void ZStack::resized(Rect newRect) {
  View::resized(newRect);
  std::for_each(child_views.begin(), child_views.end(), [&](std::shared_ptr<View> view) {
    view->resized(newRect);
  });
}

}
