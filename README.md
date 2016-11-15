# [Rubik's Cube](https://mike-leo-smith.github.io/RubiksCube/)

<big> An automatic Rubik's Cube solver written in C++, using OpenGL for graphics. </big>

## Introduction
It's just as simple as the program below...

```
#include <iostream>

int main()
{
    std::cout << "hello, world" << std::endl;
    return 0;
}
```

## Compile & Run
Before you start compiling, first make sure you have installed glfw3. Since project uses cmake to manage files, you can simply compile it use cmake and make, or use IDEs that support cmake. Also, there shouldn't be much difficulty to compile it with Visual Studio or other IDEs.

If you prefer to compile it in command-line, on Linux, type the following commands in the terminal:

```
$ g++ -o "Rubik's Cube.out" *.cpp *.h -std=c++11 -lGL -lGLU -lglfw3
```

On Windows, things are similar. If you are using g++, after setting up your environment, just type in cmd:

```
> g++ -o "Rubik's Cube.exe" *.cpp *.h -std=c++11 -lopengl32 -lglu32 -lglfw3 -Wl,--subsystem,windows
```

Commands on other platforms are similar, discover them yourself.

If you goes along well with the steps above, you will got things like "Rubik's Cube.out" or "Rubik's Cube.exe" in the directory. Double-click it to run, and now it's time to enjoy the magic steps as the Rubik's Cube restores itself...

## About

This program is developed by Mike Smith. Source codes are free for non-commercial use.
