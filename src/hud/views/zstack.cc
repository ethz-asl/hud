#include <hud/views/zstack.h>
#include <iostream>

namespace hud::views {

ZStack::ZStack(int id, const std::function<void(LayoutContext&)> &fn) : View(id) {
  fn(layout);
}

std::list<std::shared_ptr<View>> ZStack::childViews() const {
  return layout.views;
}

void ZStack::resized(Rect newRect) {
  View::resized(newRect);
  std::for_each(layout.views.begin(), layout.views.end(), [&](std::shared_ptr<View> view) {
    view->resized(newRect);
  });
}

}
