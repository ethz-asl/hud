#ifndef H_HSTACK
#define H_HSTACK
#include <vector>
#include <functional>
#include <memory>
#include "hud/views/view.h"
#include "hud/views/stack_view.h"

namespace hud::views {
class HStack : public StackView {
private:
public:
  HStack(const std::function<void(LayoutContext*)> &fn);
  HStack();
  ~HStack();
  // Management.
  void resized(Rect rect) override;
};
}

#endif
