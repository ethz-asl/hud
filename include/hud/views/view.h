#ifndef H_VIEW
#define H_VIEW
#include <functional>
#include <vector>
#include <list>
#include <memory>

#include <iostream>
namespace hud::views {

struct Rect {
  int x;
  int y;
  int width;
  int height;
};

struct ClickEvent {
  double x;
  double y;
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
  virtual void render() const = 0;

  // Event Handlers.
  void addClickHandler(ClickHandler handler) {
    click_handlers.push_back(handler);
  };
};

class LayoutContext {
public:
  std::list<std::shared_ptr<View>> views;
  void add(std::shared_ptr<View> view) { views.push_back(view); };
};

}

#endif
