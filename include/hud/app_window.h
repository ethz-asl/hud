#include <memory>
#include <GLFW/glfw3.h>
#include <hud/views/view.h>

namespace hud {

class AppWindow {
	GLFWwindow *window;
  int width, height;
  std::string title;
  std::shared_ptr<views::View> view;
public:
  AppWindow(std::string title, const int width, const int height);

  void setView(std::shared_ptr<views::View> view);
  ~AppWindow();

  // Mouse Input.
  void leftClick();

  // Window handlers.
  void resized(int, int);

  // Rendering.
  bool update();
};

}
