import hud
import time

def main():
    window = hud.AppWindow("Labeler", 1280, 600)

    points = [hud.Point(0.0, 0.0)]
    left_image = hud.ImagePane("../assets/left.jpg")
    point_layer = hud.PointLayer(points)
    def add_layer(context):
        context.add(left_image)
        context.add(point_layer)

    left_pane = hud.ZStack(add_layer)
    right_pane = hud.ImagePane("../assets/right.png")

    def add_views(context):
        context.add(left_pane)
        context.add(right_pane)

    hstack = hud.HStack(add_views)

    window.setView(hstack)

    while window.update():
        time.sleep(0.1)
        window.waitEvents()

if __name__ == "__main__":
    main()
    hud.shutdown()


