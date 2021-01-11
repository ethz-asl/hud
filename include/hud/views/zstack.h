#ifndef H_ZSTACK
#define H_ZSTACK
#include <hud/views/view.h>

namespace hud::views {
class ZStack : public hud::views::View {
private:
public:
  ZStack(int id, const std::function<void(LayoutContext*)> &);
  // Management.
  void resized(Rect rect) override;
};
}

#endif
