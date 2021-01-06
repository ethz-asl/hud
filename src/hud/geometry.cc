#include <hud/geometry.h>

std::ostream& operator<<(std::ostream& os, const Rect& rect) {
  return os << "Rect(x=" << rect.x << ", y=" << rect.y << ", width=" << rect.width << ", height=" << rect.width << ")";
}
std::ostream& operator<<(std::ostream& os, const Point& point) {
  return os << "Point(x=" << point.x << ", y=" << point.y << ")";
}
