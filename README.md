# Flappy Bird

# Table of content
- [About](#About)
- [How to Run](#How-to-run)
- [How to build](#How-to-build)
- [Features](#Features)
 
# About
A clone of the Flappy Bird game made with the [SFML](https://www.sfml-dev.org/) library. Game recreated for the purpose of learning more about neural networks and game development.

# How to run
There is an executable for windows in the "Game.zip" folder

# How to build
  ## Requirements
  - [CMake](https://cmake.org/)
  - [SFML](https://www.sfml-dev.org/)
  - [c++ compiler](https://sourceforge.net/projects/mingw-w64/)  
  * Follow this [tutorial](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php) for more detail

  ## Cloning
   ```bash
  # Clone repository
  $ git clone https://github.com/Thalisson-Alves/Flappy-Bird
  
  # Go to Flappy Bird directory
  $ cd Flappy-Bird
  ```

  ## Building
  In Flappy-Bird directory run this commands. Note that I'm using MinGW Makefiles, so you may have to change this. 
  ```bash
  # Create and switch to the build directory
  $ mkdir build
  $ cd build

  # Run cmake. On '-G' flag change to the compiler you are using.
  $ cmake.exe -G "MinGW Makefiles" -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++ ../

  # Type the make command of the compiler you are using.
  $ mingw32-make
  ```

  Now you have the executable called inside build directory. Copy or move the dlls files from Game.zip to the same folder as the executable and you are ready to run it ;)

# Features
Some features that I'm working on
- [X] End game state
- [ ] Score
- [ ] Neural network
    - [ ] Load a model
    - [ ] Save a model
- [ ] Music / sound
- [ ] Settings state
