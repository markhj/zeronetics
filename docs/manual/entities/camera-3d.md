@page camera-3d 3D camera

The ZEN::Camera3D entity provides essential information to the renderer
in order to view 3D scenes.

For a 3D camera you need to define a number of properties to accurately
depict perspective.

## 📐 Aspect ratio

The **aspect ratio** is the relationship between the window's width
and height. You calculate it by diving the window width by the
window height. You can get these values from ZEN::Settings.

The default value on the camera is ``1.777`` which corresponds
to a standard 1920x1080 monitor.

@note You must update the aspect ratio, when you apply new monitor settings.

@warning If you don't accurately set the aspect ratio to match the window
proportions, the scene will render, but it might look stretched and off.

## 👀 Field of view

The **field of view** is the angle the camera can see.

The value is given in radians.

Default value corresponds to approx. 45&deg;.

## ✂️ Clipping plane

The **clipping plane** defines the visible space ahead of the camera.
It has a "near" and a "far" value. Anything outside this space
will not be rendered (i.e. it will be _clipped_).
