# Exercise GameUsing Motion Detection (College mini project)

## Team Members
* [Ameer](https://www.example.com)
* [Anas](https://www.example.com)
* [Hemanth](https://github.com/Hemanth3303)
* [Jibin](https://www.example.com)

## What is this?
* This is an exercise game.
* Player is controlled by real life movements.
* It uses motion detection for this.
* This is a group mini project as part of college curriculum.

##  Dependencies
* Made using C++
* [CMake](https://cmake.org/) as build system
* [Vcpkg](https://vcpkg.io/en/) to manage library dependencies
* Libraries used: 
  * [Raylib](https://www.raylib.com/) : for graphics
  * [OpenCV](https://opencv.org/) : for motion detection


## Build Instructions
* You need to have git, cmake, vcpkg and a C++ compiler supporting C++20 features installed on your system.
* VCPKG_ROOT environment variable must be set.
* Clone this repo:
```shell
git clone https://github.com/Hemanth3303/ExerciseGameUsingMotionDetection.git
```
* Use vcpkg to install the dependencies
```shell
vcpkg install raylib opencv
```
* In the root of the project, run cmake with preferred preset
```shell
cmake -S . -B build --preset=windows_x86-64_debug
```
* build
```shell
cmake --build build
```
* run the executable found at ./build/Debug/