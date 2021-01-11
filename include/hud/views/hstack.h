#ifndef H_HSTACK
#define H_HSTACK
#include <vector>
#include <functional>
#include <memory>
#include <hud/views/view.h>

namespace hud::views {
class HStack : public View {
private:
public:
  HStack(const std::function<void(LayoutContext*)> &fn);
  ~HStack();
  // Management.
  void resized(Rect rect) override;
};
}

#endif
