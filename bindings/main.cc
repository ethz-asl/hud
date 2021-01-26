#include "hud/utils.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>
#include "hud/app_window.h"
#include "hud/views/stack_view.h"
#include "hud/views/hstack.h"
#include "hud/views/zstack.h"
#include "hud/views/point_layer.h"
#include "hud/views/line_layer.h"
#include "hud/views/pane.h"
#include "hud/bindings/numpy_utils.h"
#include "hud/shader_utils.h"

namespace py = pybind11;
using namespace hud;
using namespace hud::views;

PYBIND11_MODULE(hud, m) {
  py::class_<ClickEvent>(m, "ClickEvent")
    .def_readonly("p", &ClickEvent::p);
  py::class_<KeyEvent>(m, "KeyEvent")
    .def_readonly("key", &KeyEvent::key)
    .def_readonly("modifiers", &KeyEvent::modifiers);

  py::class_<Rect>(m, "Rect")
    .def(py::init<double, double, double, double>())
    .def_readonly("x", &Rect::x)
    .def_readonly("y", &Rect::y)
    .def_readonly("width", &Rect::width)
    .def_readonly("height", &Rect::height);

  py::class_<View, std::shared_ptr<View>> view(m, "View");
  view.def("get_rect", &View::getRect)
    .def("add_click_handler", &View::addClickHandler);

  py::class_<StackView, std::shared_ptr<StackView>> stack_view(m, "StackView", view);
  stack_view.def("add_view", &StackView::addView);

  py::class_<Point>(m, "Point")
    .def(py::init<double, double>())
    .def(py::init<>())
    .def_readonly("x", &Point::x)
    .def_readonly("y", &Point::y);

  py::class_<ImagePane, std::shared_ptr<ImagePane>>(m, "ImagePane", view)
    .def(py::init<>())
    .def(py::init<std::string>())
    .def("set_texture", [](ImagePane& pane, py::array_t<uint8_t> array) {
      auto texture = hud::numpy_utils::arrayToTexture(array);
      pane.setTexture(texture);
    });

  py::class_<HStack, std::shared_ptr<HStack>>(m, "HStack", stack_view)
    .def(py::init<>())
    .def(py::init<std::function<void(LayoutContext*)>>());

  py::class_<ZStack, std::shared_ptr<ZStack>>(m, "ZStack", stack_view)
    .def(py::init<>())
    .def(py::init<std::function<void(LayoutContext*)>>());

  py::class_<PointLayer, std::shared_ptr<PointLayer>>(m, "PointLayer", view)
    .def(py::init<const std::vector<Point>>())
    .def("set_points", &PointLayer::setPoints)
    .def("add_point", &PointLayer::addPoint)
    .def("set_colors", &PointLayer::setColors)
    .def("pop", &PointLayer::pop)
    .def("clear_points", &PointLayer::clearPoints);

  py::class_<LineLayer, std::shared_ptr<LineLayer>>(m, "LineLayer", view)
    .def(py::init<>())
    .def("set_line", &LineLayer::setLine);

  py::class_<LayoutContext>(m, "LayoutContext")
    .def(py::init<>())
    .def("add", &LayoutContext::add);

  py::class_<AppWindow>(m, "AppWindow")
    .def(py::init<std::string, int, int>())
    .def("wait_events", &AppWindow::waitEvents)
    .def("add_key_handler", &AppWindow::addKeyHandler)
    .def("set_view", &AppWindow::setView)
    .def("update", &AppWindow::update);

  m.def("shutdown", &utils::shutdown);

  auto modifiers = m.def_submodule("modifiers");
  modifiers.attr("SHIFT") = modifiers::Shift;
  modifiers.attr("CTRL")  = modifiers::Ctrl;
  modifiers.attr("ALT")   = modifiers::Alt;

  m.def("set_data_directory", &shader_utils::setDataDirectory);

  auto utils = m.def_submodule("utils");
  utils.def("to_normalized_device_coordinates", &utils::toNormalizedDeviceCoordinates)
    .def("scale_to_view", &utils::scaleToView);

}


