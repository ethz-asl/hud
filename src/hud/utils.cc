#include <hud/utils.h>

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
}
