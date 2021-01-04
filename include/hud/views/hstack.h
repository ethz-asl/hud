#ifndef H_HSTACK
#define H_HSTACK
#include <vector>
#include <functional>
#include <memory>
#include <hud/views/view.h>

namespace views {
struct Layout {
  std::vector<std::shared_ptr<View>> views;
};

class HStack : public View {
private:
  Layout layout;
public:
  HStack(int id, const std::function<void(Layout&)> &fn);
  ~HStack();
  void render(const ViewRect& rect);
};
}

#endif
