#ifndef H_UTILS
#define H_UTILS
#include <hud/geometry.h>

namespace hud::utils {
bool intersects(const Point& p, const Rect&rect);
Point toNormalizedDeviceCoordinates(const Point& p, const Rect& rect);
void shutdown();
}
#endif
