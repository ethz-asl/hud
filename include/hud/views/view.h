#ifndef H_VIEW
#define H_VIEW
#include <hud/common.h>
#include <functional>
#include <vector>
#include <list>
#include <memory>
#include <hud/geometry.h>
#include <hud/utils.h>
#include <bgfx/bgfx.h>

namespace hud::views {
struct ClickEvent {
  Point p;
};

using ClickHandler = std::function<bool(const ClickEvent&)>;

class View {
protected:
  std::vector<ClickHandler> click_handlers;
  Rect rect;
public:
  const int view_id;
  View(int id) : view_id(id) {
    rect = { 0, 0, 0, 0 };
  }

  // Management.
  virtual std::list<std::shared_ptr<View>> childViews() const {
    return std::list<std::shared_ptr<View>>();
  }
  virtual void resized(Rect newRect) {
    rect = newRect;
  }
  const Rect& getRect() { return rect; }

  // Rendering.
  virtual void render() const {
    for (auto view : this->childViews()) {
      auto rect = view->getRect();
      bgfx::setViewRect(view->view_id, rect.x, rect.y, rect.width, rect.height);
      view->render();
    }
  }

  // Event Handling.
  void addClickHandler(ClickHandler handler) {
    click_handlers.push_back(handler);
  };

  virtual bool leftClick(const ClickEvent& event) {
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
};

class LayoutContext {
public:
  std::list<std::shared_ptr<View>> views;
  void add(std::shared_ptr<View> view) { views.push_back(std::move(view)); };
};

}

#endif
