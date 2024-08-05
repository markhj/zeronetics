@page lights-tutorial Working with lights

In this tutorial we're examining the basics of working with lights
in Zeronetics.

## 🔍 How it works

In essence, you need to have a **shader with light calculations**.

If you're relying on the native @ref shader-builder "Shader Builder"
in Zeronetics, you add the following to the ZEN::ShaderBlueprint 
"shader blueprint":

````cpp
ZEN::ShaderBlueprint blueprint{
    // Other settings
    .lightSupport = {
            .slotsDirectionalLight3D = 1,
            .slotsPointLight3D = 20,
    },
};
````

You can modify the number of slots to match your use-case.

All @ref ZEN::ILight "lights" are equipped with a method name
ZEN::ILight::setOnShader "setOnShader" where you pass the shader
in question, such that information about the light is added as uniform.

That's basically:

````cpp
myLight->setOnShader(shader);
````

## 🔦 Types of light

There are currently two types of 3D lights, with more being added some time
in the future.

### 🔆 Directional light

In most instances, you can think of
@ref ZEN::DirectionalLight3D "directional light"
as sunlight, because directional light works _everywhere_ in a  scene.

From a technical perspective it's said that directional lights
have direction but not position.

You add directional light to your scene with ZEN::DirectionalLight3D:

````cpp
DirectionalLight3D sun;
sun.direction = Vec3(0.0, -1.0, 0.0);
````

You can modify the direction to your liking. This example shines straight
down on the scene.

Now, add it to any shader which is subject to such light with:

````cpp
sun.setOnShader(someShader);
````

### 💡 Point light

Point lights can be thought of as light bulbs. They have a position, but
no specific direction. They can only light up a limited part of a scene.

The @ref ZEN::PointLight3D "point light" is almost identical in
setup to directional light, only you also need to specify a position.

````cpp
PointLight3D pointLight;
pointLight.position = Vec3(2.0, 1.0, -2.0);
````

Like before, it must also be set on any shader where it must have
an effect.

````cpp
pointLight.setOnShader(someShader);
````

## 🔌 Let there be light!

That's it! You should now have light in your scene.

For further more information it's recommended to check 
ZEN::DirectionalLight3D and ZEN::PointLight3D, because there are a
number of additional properties you can work with, including 
color.
