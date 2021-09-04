# led-inosaures

## Clone

Clone me with

```
git clone --recursive https://github.com/JulesFouchy/led-inosaures
```

## Build

⚠️ You need a C++ 20 compiler.

Build with CMake :

Install [CMake](https://cmake.org/download/). If you already have it, make sure you have version 3.16 or later.

Then, I recommend this VS Code extension : [ms-vscode.cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools).

Finally you will need to setup the extension with a compiler. Here is [the tutorial](https://code.visualstudio.com/docs/cpp/cmake-linux). It is based on Linux but at the bottom of the page you will find the explanations to adapt it for [Windows](https://code.visualstudio.com/docs/cpp/config-msvc) and [Mac](https://code.visualstudio.com/docs/cpp/config-clang-mac).

## Try the app

Once this builds, you should see ![this](/illustration.png)

The menu on the right allows you to switch between the different effects. Now, let's add your own !

## Write some effects !

Go to *src/Effects* and duplicate *Gradient.h*. Then rename the file and the class inside to your liking, and start tweaking the ```apply``` function.

To register your effect, you will need to go in *_AllEffects.h* and :
- __*STEP 1 :*__ ```#include``` your file
- __*STEP 2 :*__ Add it to the list of variants for an Effect ```using Effect = std::variant< . . .```
- __*STEP 3 :*__ Register your effect by giving it a name that will be displayed in the dropdown of all the effects : ```    register_effect<Gradient>("Gradient", e);``` **NB :** You must register you effect last, and not alter the order of the previous effects, otherwise this will mess up serialization !
```cpp
register_effect<Gradient>("Gradient", e);
register_effect<ConstantColor>("Constant Color", e);
// Your new effect goes here, last
```