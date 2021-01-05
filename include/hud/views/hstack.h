#ifndef H_HSTACK
#define H_HSTACK
#include <vector>
#include <functional>
#include <memory>
#include <hud/views/view.h>

namespace hud::views {
class HStack : public View {
private:
  LayoutContext layout;
public:
  HStack(int id, const std::function<void(LayoutContext&)> &fn);
  ~HStack();
  // Management.
  virtual std::list<std::shared_ptr<View>> childViews() const override;
  void resized(Rect rect) override;

  // Rendering.
  void render() const override;
};
}

#endif
