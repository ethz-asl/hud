#include <bgfx/bgfx.h>
#include "views/hstack.h"
#include <iostream>

namespace views {

const int Padding = 5;

HStack::HStack(int id, const std::function<void(Layout&)> &fn) : View(id) {
  fn(layout);
}

HStack::~HStack() {}

void HStack::render(const ViewRect& rect) {
  int viewCount = layout.views.size();
  int viewsWidth = rect.width - 2 * Padding - (viewCount - 1) * Padding;
  int viewHeight = rect.height - 2 * Padding - (viewCount - 1) * Padding;
  int singleViewWidth = (viewsWidth - (viewCount - 1) * Padding) / viewCount;
  int startX = Padding;
  std::for_each(layout.views.begin(), layout.views.end(), [&, i = 0](std::shared_ptr<View> view) mutable {
    ViewRect rect = { startX + (singleViewWidth + Padding) * i, Padding, singleViewWidth, viewHeight };
    bgfx::setViewRect(view->viewId, rect.x, rect.y, rect.width, rect.height);
    view->render(rect);
    i++;
  });
}

}
