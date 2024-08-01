@page settings Settings

The ZEN::Settings object assist with managing settings for 
window, video, audio, etc.

It does not concern itself directly with mapping of keys and
other controls because this is implemented by other classes in
Zeronetics.

## 📺 Generating the window

The ZEN::Window is generated with a set of settings. You
can modify them prior to generating, or re-generate when you see
fit (for instance, when the player clicks "Apply settings" or 
similar).

### Example

We initialize with a resolution of 800x600.

````cpp
ZEN::Settings settings {
    .screenResolution = {800, 600},
};

window.generate(settings);
````

Then the user heads into the "Settings" menu in your game and changes the
resolution. Now, you use ZEN::Window::regenerate.

````cpp
settings.screenResolution = {1920, 1080};

window.regenerate(settings);
````

@note Remember to
@ref a-camera-aspect-ratio "update the camera's aspect ratio property"
when the monitor resolution changes.

## 🔧 List of settings

| Setting              | Value                 | Default        | Description                             |
|----------------------|-----------------------|----------------|-----------------------------------------|
| ``screenResolution`` | ZEN::ScreenResolution | ``{960, 540}`` | Monitor resolution                      |
| ``antiAlias``        | ZEN::AntiAlias        | ``MSAA4X``     | Smoothing of pixelated edges            |
| ``vSync``            | ``bool``              | ``true``       | Enable/disable vertical sync. (V-Sync). |
