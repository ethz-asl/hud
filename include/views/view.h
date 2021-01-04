#ifndef H_VIEW
#define H_VIEW
namespace views {

struct ViewRect {
  int x;
  int y;
  int width;
  int height;
};

class View {
public:
  int viewId;
  View(int id) : viewId(id) {}
  virtual void render(const ViewRect&) = 0;
};
}

#endif
