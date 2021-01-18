#include <memory>
#include <GLFW/glfw3.h>
#include <hud/views/view.h>

namespace hud {

struct KeyEvent {
  const char key;
  const int modifiers;
};
using KeyHandler = std::function<void(const KeyEvent&)>;

namespace modifiers {
  const int static Shift = 0b001;
  const int static Ctrl  = 0b010;
  const int static Alt   = 0b100;
};

class AppWindow {
	GLFWwindow *window;
  int width, height;
  std::list<KeyHandler> key_handlers;
  std::string title;
  std::shared_ptr<views::View> view;
public:
  AppWindow(std::string title, const int width, const int height);
  ~AppWindow();

  void setView(std::shared_ptr<views::View> view);

  void addKeyHandler(KeyHandler& handler) {
    key_handlers.push_back(handler);
  }

  void waitEvents() const {
    glfwWaitEvents();
  }

  // Window handlers.
  void resized(int, int);

  // Rendering.
  bool update();

private:
  // Input events.
  void leftClick();
  void keydown(const KeyEvent& event);
};

}
