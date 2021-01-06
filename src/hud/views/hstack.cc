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
  double viewCount = layout.views.size();
  double viewsWidth = rect.width - 2 * Padding - (viewCount - 1) * Padding;
  double viewHeight = rect.height - 2 * Padding - (viewCount - 1) * Padding;
  double singleViewWidth = (viewsWidth - (viewCount - 1) * Padding) / viewCount;
  double startX = Padding;
  std::for_each(layout.views.begin(), layout.views.end(), [&, i = 0](std::shared_ptr<View> view) mutable {
    Rect rect = { startX + (singleViewWidth + Padding) * i, Padding, singleViewWidth, viewHeight };
    view->resized(rect);
    i++;
  });
}

}
