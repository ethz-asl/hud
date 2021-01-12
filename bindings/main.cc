#include "hud/utils.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include "hud/app_window.h"
#include "hud/views/hstack.h"
#include "hud/views/zstack.h"
#include "hud/views/point_layer.h"
#include "hud/views/pane.h"
#include "hud/bindings/numpy_utils.h"

namespace py = pybind11;
using namespace hud;
using namespace hud::views;

PYBIND11_MODULE(hud, m) {
  py::class_<ClickEvent>(m, "ClickEvent")
    .def_readonly("p", &ClickEvent::p);

  py::class_<Rect>(m, "Rect")
    .def_readonly("x", &Rect::x)
    .def_readonly("y", &Rect::y)
    .def_readonly("width", &Rect::width)
    .def_readonly("height", &Rect::height);

  py::class_<View, std::shared_ptr<View>> view(m, "View");
  view.def("getRect", &View::getRect)
    .def("add_click_handler", &View::addClickHandler);

  py::class_<Point>(m, "Point")
    .def(py::init<double, double>());

  py::class_<ImagePane, std::shared_ptr<ImagePane>>(m, "ImagePane", view)
    .def(py::init<std::string>())
    .def("set_texture", [](ImagePane& pane, py::array_t<uint8_t> array) {
      auto texture = hud::numpy_utils::arrayToTexture(array);
      pane.setTexture(texture);
    });

  py::class_<HStack, std::shared_ptr<HStack>>(m, "HStack", view)
    .def(py::init<std::function<void(LayoutContext*)>>());

  py::class_<ZStack, std::shared_ptr<ZStack>>(m, "ZStack", view)
    .def(py::init<std::function<void(LayoutContext*)>>());

  py::class_<PointLayer, std::shared_ptr<PointLayer>>(m, "PointLayer", view)
    .def(py::init<const std::vector<Point>>())
    .def("set_points", &PointLayer::setPoints)
    .def("add_point", &PointLayer::addPoint);

  py::class_<LayoutContext>(m, "LayoutContext")
    .def(py::init<>())
    .def("add", &LayoutContext::add);

  py::class_<AppWindow>(m, "AppWindow")
    .def(py::init<std::string, int, int>())
    .def("wait_events", &AppWindow::waitEvents)
    .def("set_view", &AppWindow::setView)
    .def("update", &AppWindow::update);

  m.def("shutdown", &utils::shutdown);

  auto utils = m.def_submodule("utils");
  utils.def("to_normalized_device_coordinates", &utils::toNormalizedDeviceCoordinates);
}
