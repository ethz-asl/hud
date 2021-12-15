import os
import hud
import time
import numpy as np
from PIL import Image

POINT_COLOR = np.array([1.0, 0.6, 0.5, 1.0])

def main():
    window = hud.AppWindow("Image point example", 1280, 360)

    points = []
    left_image = hud.ImagePane("./assets/kitchen.jpg")
    point_layer = hud.PointLayer(points)
    def add_layer(context):
        context.add(left_image)
        context.add(point_layer)

    def add_point(event):
        p = hud.utils.to_normalized_device_coordinates(event.p, left_pane.get_rect())
        point_layer.add_point(p, POINT_COLOR)
        return True

    left_image.add_click_handler(add_point)
    left_pane = hud.ZStack(add_layer)
    right_pane = hud.ImagePane("./assets/kitchen.jpg")


    hstack = hud.HStack()
    hstack.add_view(left_pane)
    hstack.add_view(right_pane)

    window.set_view(hstack)

    while window.update():
        time.sleep(0.1)
        window.wait_events()

if __name__ == "__main__":
    main()
    hud.shutdown()


