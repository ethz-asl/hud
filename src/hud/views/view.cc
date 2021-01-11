#include <hud/views/view.h>


namespace hud::views {

class IDCounter {
  int id_counter;
public:
  IDCounter() {
    id_counter = 0;
  }
  IDCounter(const IDCounter&) = delete;
  void operator=(const IDCounter&) = delete;
  static IDCounter& getInstance() {
    static IDCounter instance;
    return instance;
  }

  int next() {
    int id = id_counter;
    id_counter++;
    return id;
  }
};

View::View() : view_id(IDCounter::getInstance().next()) {
  rect = { 0, 0, 0, 0 };
}

const std::list<std::shared_ptr<View>>& View::childViews() const {
  return child_views;
}

void View::resized(Rect newRect) {
  rect = newRect;
}

void View::render() const {
  for (auto view : this->childViews()) {
    auto rect = view->getRect();
    bgfx::setViewRect(view->view_id, rect.x, rect.y, rect.width, rect.height);
    view->render();
  }
}

bool View::leftClick(const ClickEvent& event) {
  bool click_handled = false;
  for (auto child_view : childViews()) {
    const Rect& view_rect = child_view->getRect();
    if (hud::utils::intersects(event.p, view_rect)) {
      const ClickEvent local_event = { Point(event.p.x - view_rect.x, event.p.y - view_rect.y) };
      click_handled = click_handled || child_view->leftClick(local_event);
    }
  }

  if (!click_handled) {
    for (auto handler : click_handlers) {
      handler(event);
    }
  }
  return true;
};

}
