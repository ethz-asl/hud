#ifndef H_ZSTACK
#define H_ZSTACK
#include <hud/views/view.h>

namespace hud::views {
class ZStack : public hud::views::View {
private:
  LayoutContext layout;
public:
  ZStack(int id, const std::function<void(LayoutContext&)> &);
  // Management.
  virtual std::list<std::shared_ptr<View>> childViews() const override;
  void resized(Rect rect) override;
};
}

#endif
