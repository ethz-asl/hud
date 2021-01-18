#ifndef H_ZSTACK
#define H_ZSTACK
#include "hud/views/view.h"
#include "hud/views/stack_view.h"

namespace hud::views {
class ZStack : public hud::views::StackView {
private:
public:
  ZStack();
  ZStack(const std::function<void(LayoutContext*)> &);
  // Management.
  void resized(Rect rect) override;
};
}

#endif
