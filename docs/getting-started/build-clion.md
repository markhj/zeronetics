@page build-clion Build engine with CLion

This guide details how to build Zeronetics using
[JetBrains CLion](https://www.jetbrains.com/clion/).

## ☝️ First of all

Make sure you have
@ref install-engine-clone "cloned the engine"
and
@ref install-engine-submodules "initialized the submodules".

If you've opened CLion before initializing the submodules, you
might see error messages. In that case, run **Re-Load CMake Project**.

## 🚀 Release build

Optionally, you can add a **Release** profile. Release builds
are significantly faster that debug builds, but obviously also
lack a lot of the debugging tools we often rely on.

From the menu with the profiles next to the **Run / Debug configuration**
menu, select **Edit CMake Profiles...**.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1722409378/zeronetics/image_2024-07-31_090254103_hohvdh.png)

From the box which opens, click on the "+" above the list of profiles.
Usually, CLion automatically suggests a profile named "Release," and if
you're using a regular CLion installation, you actually don't need
to anything else.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1722409464/zeronetics/image_2024-07-31_090421485_fmgfon.png)

## 🔨 Build

Now, you can build a specific part of the project, or build it in
its entirety from the **Build** menu.

![](https://res.cloudinary.com/drfztvfdh/image/upload/v1722409594/zeronetics/image_2024-07-31_090631962_k0imhv.png)

## 💫 What's next?

Once the build process is completed which shouldn't take more than a few
minutes, at most, you can continue with 
@ref setting-up-a-game.
