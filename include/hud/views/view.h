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

enum Key {
};

struct ClickEvent {
  const Point p;
};

using ClickHandler = std::function<bool(const ClickEvent&)>;

class View {
protected:
  std::list<ClickHandler> click_handlers;
  Rect rect;
  std::list<std::shared_ptr<View>> child_views;
public:
  const int view_id;
  View();

  // Management.
  virtual const std::list<std::shared_ptr<View>>& childViews() const;
  virtual void resized(Rect newRect);
  const Rect& getRect() { return rect; }

  // Rendering.
  virtual void render() const;
  // Event Handling.
  void addClickHandler(ClickHandler handler) {
    click_handlers.push_back(handler);
  };

  virtual bool leftClick(const ClickEvent& event);
};

class LayoutContext {
public:
  std::list<std::shared_ptr<View>> views;
  void add(std::shared_ptr<View> view) {
    views.push_back(std::move(view));
  };
};

}

#endif
