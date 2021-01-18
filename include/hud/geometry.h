#ifndef H_GEOMETRY
#define H_GEOMETRY
#include <initializer_list>
#include <iostream>

struct Rect {
  double x;
  double y;
  double width;
  double height;
  Rect(double x, double y, double w, double h) : x(x), y(y), width(w), height(h) {}
  Rect() : x(0.0), y(0.0), width(0.0), height(0.0) {}
};

struct Point {
  double x;
  double y;
  Point() : x(0.0), y(0.0) {}
  Point(double x, double y) : x(x), y(y) {}
  Point operator*(double value) {
    return Point(x * value, y * value);
  }
  Point operator+(double value) {
    return Point(x + value, y + value);
  }
  Point operator-(double value) {
    return Point(x - value, y - value);
  }
};

std::ostream& operator<<(std::ostream& os, const Rect& rect);
std::ostream& operator<<(std::ostream& os, const Point& point);

#endif
