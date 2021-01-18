#include <hud/utils.h>
#include <bgfx/bgfx.h>
#include <GLFW/glfw3.h>

namespace hud::utils {

bool intersects(const Point& p, const Rect& rect) {
  if (p.x > rect.x &&
      p.x < rect.x + rect.width &&
      p.y > rect.y &&
      p.y < rect.y + rect.height) {
    return true;
  } else {
    return false;
  }
}


Point toNormalizedDeviceCoordinates(const Point& p, const Rect& rect) {
  return Point(p.x / rect.width * 2.0 - 1.0, p.y / rect.height * -2.0 + 1.0);
}

Point scaleToView(const Point& p, const Rect& source_rect, const Rect& target_rect) {
  double x, y;
  x = p.x / source_rect.width * target_rect.width;
  y = p.y / source_rect.height * target_rect.height;
  return Point(x, y);
}

void shutdown() {
  bgfx::shutdown();
  glfwTerminate();
}
}
