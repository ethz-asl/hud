#include <memory>
#include <vector>
#include <GLFW/glfw3.h>
#include "views/pane.h"

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
  std::vector<std::pair<Rect, std::shared_ptr<views::Pane>>> panes;
public:
  AppWindow(std::string title);

  void addPane(std::shared_ptr<views::Pane> pane);
  ~AppWindow();

  void resized(int, int);
  bool update();
};

