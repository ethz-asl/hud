#ifndef H_STACK_VIEW
#define H_STACK_VIEW
#include "hud/views/view.h"

namespace hud::views {

class StackView : public View {
public:
  void addView(std::shared_ptr<View> view);
};
}

#endif
