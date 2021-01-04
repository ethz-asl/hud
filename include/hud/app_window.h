#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include <hud/views/pane.h>

struct Rect {
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
};

class AppWindow {
	GLFWwindow *window;
  int width, height;
  std::string title;
  std::shared_ptr<views::View> view;
public:
  AppWindow(std::string title, const int width, const int height);

  void setView(std::shared_ptr<views::View> view);
  ~AppWindow();

  void resized(int, int);
  bool update();
};

