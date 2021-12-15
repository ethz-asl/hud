# HUD

The goal of HUD, is to be able to *extremely* quickly put together a graphical interface. It is built on [bgfx](https://github.com/bkaradzic/bgfx), and therefore supports many rendering backends, including OpenGL, Metal and Vulkan.

It can be used either directly through the C++ interface or through the Python bindings.

It built around views. Currently supported views are:
- `ImagePane` - shows an image.
- `PointLayer` - renders points in 2D.
- `ZStack` - Stacks views on top of each other.
- `HStack` - Stacks views horizontally.

Views are rendered by `hud.AppWindow`. It is easy to key handlers to the window using `.add_key_handler` to respond to key events.

Click handlers can be attached to views to do something when the user clicks the view.

## Installing python bindings

`sudo apt-get install libglfw3-dev libeigen3-dev libboost-dev`

```
git submodule update --init --recursive
mkdir build && cd build &&
cmake .. -DCMAKE_BUILD_TYPE=Release &&
make -j4
```

Install bindings with `pip install .`.

## Examples

The example `examples/python/stereo_image.py` shows a small example which uses the `HStack`, `ImagePane`, `ZStack` and `PointLayer` views.

Run it with `python examples/python/stereo_image.py`.

