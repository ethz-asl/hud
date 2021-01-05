#include <bgfx/bgfx.h>
#include <hud/views/hstack.h>
#include <iostream>

namespace hud::views {

const int Padding = 5;

HStack::HStack(int id, const std::function<void(LayoutContext&)> &fn) : View(id) {
  fn(layout);
}

HStack::~HStack() {}

std::list<std::shared_ptr<View>> HStack::childViews() const {
  return layout.views;
}

void HStack::resized(Rect newRect) {
  View::resized(newRect);
  int viewCount = layout.views.size();
  int viewsWidth = rect.width - 2 * Padding - (viewCount - 1) * Padding;
  int viewHeight = rect.height - 2 * Padding - (viewCount - 1) * Padding;
  int singleViewWidth = (viewsWidth - (viewCount - 1) * Padding) / viewCount;
  int startX = Padding;
  std::for_each(layout.views.begin(), layout.views.end(), [&, i = 0](std::shared_ptr<View> view) mutable {
    Rect rect = { startX + (singleViewWidth + Padding) * i, Padding, singleViewWidth, viewHeight };
    view->resized(rect);
    i++;
  });
}

void HStack::render() const {
  for (auto view : this->childViews()) {
    auto rect = view->getRect();
    bgfx::setViewRect(view->view_id, rect.x, rect.y, rect.width, rect.height);
    view->render();
  }
}

}
