import hud
import time
import numpy as np
from PIL import Image

def main():
    window = hud.AppWindow("Labeler", 1280, 600)

    points = [hud.Point(0.0, 0.0)]
    left_image = hud.ImagePane("../assets/left.jpg")
    point_layer = hud.PointLayer(points)
    def add_layer(context):
        context.add(left_image)
        context.add(point_layer)

    def add_point(event):
        p = hud.utils.to_normalized_device_coordinates(event.p, left_pane.getRect())
        point_layer.add_point(p)
        return True

    left_image.add_click_handler(add_point)
    left_pane = hud.ZStack(add_layer)
    right_pane = hud.ImagePane("../assets/right.jpg")

    images = ["../assets/right.jpg", "../assets/left.jpg"]

    def swap_image(event):
        current_image = images[0]
        next_image = images[1]
        images[0] = next_image
        images[1] = current_image
        image = np.array(Image.open(next_image))
        right_pane.set_texture(image)

    right_pane.add_click_handler(swap_image)

    def add_views(context):
        context.add(left_pane)
        context.add(right_pane)

    hstack = hud.HStack(add_views)

    window.set_view(hstack)

    while window.update():
        time.sleep(0.1)
        window.wait_events()

if __name__ == "__main__":
    main()
    hud.shutdown()


