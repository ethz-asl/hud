#include "hud/views/stack_view.h"

namespace hud::views {
void StackView::addView(std::shared_ptr<View> view) {
  child_views.push_back(view);
}
}
