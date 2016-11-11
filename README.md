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
To compile it on Linux using g++, first make sure you have installed proper versions of OpenGL and freeglut, and then type the following commands in the terminal:

```
$ g++ *.cpp *.h -std=c++11 -lGL -lGLU -lglut
```

And run it by simply typing:

```
$ ./a.out
```

Then input a number as the seed for the random number generator, so it will have different cubes to solve, and enjoy the magic steps as the Rubik's Cube restores itself...

Approach to compiling and running it on other platforms should be similar. Discover it yourself!

## About

This program is developed by Mike Smith. Source codes are free for non-commercial use.
