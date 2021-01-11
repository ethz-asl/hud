#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <hud/app_window.h>
#include <hud/views/hstack.h>
#include <hud/views/zstack.h>
#include <hud/views/point_layer.h>
#include <hud/views/pane.h>

namespace py = pybind11;
using namespace hud;
using namespace hud::views;

PYBIND11_MODULE(hud, m) {
  py::class_<View, std::shared_ptr<View>> view(m, "View");
  view.def("getRect", &View::getRect);

  py::class_<Point>(m, "Point")
    .def(py::init<double, double>());

  py::class_<ImagePane, std::shared_ptr<ImagePane>>(m, "ImagePane", view)
    .def(py::init<std::string>());

  py::class_<HStack, std::shared_ptr<HStack>>(m, "HStack", view)
    .def(py::init<std::function<void(LayoutContext*)>>());

  py::class_<ZStack, std::shared_ptr<ZStack>>(m, "ZStack", view)
    .def(py::init<std::function<void(LayoutContext*)>>());

  py::class_<PointLayer, std::shared_ptr<PointLayer>>(m, "PointLayer", view)
    .def(py::init<const std::vector<Point>>())
    .def("setPoints", &PointLayer::setPoints);

  py::class_<LayoutContext>(m, "LayoutContext")
    .def(py::init<>())
    .def("add", &LayoutContext::add);

  py::class_<AppWindow>(m, "AppWindow")
    .def(py::init<std::string, int, int>())
    .def("waitEvents", &AppWindow::waitEvents)
    .def("setView", &AppWindow::setView)
    .def("update", &AppWindow::update);

  m.def("shutdown", &utils::shutdown);

}
