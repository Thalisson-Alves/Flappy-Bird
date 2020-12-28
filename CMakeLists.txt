#sets up the minimum version of cmake
cmake_minimum_required(VERSION 3.9)

#how the project will be called
project (flappy_bird)

#set the C++ standard to be used
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -pedantic")

#set source files
set (SOURCE_FILES 
	src/main.cpp 
	src/Application.cpp
	src/Bird.cpp 
	src/Entity.cpp
	src/Pipe.cpp
	src/Random.cpp
	src/Utility.cpp
	src/State.cpp
	src/StateStack.cpp
	src/MenuState.cpp
	src/GameState.cpp
	src/PauseState.cpp
	src/World.cpp
	src/Component.cpp
	src/Button.cpp
	src/Container.cpp
	src/GameOverState.cpp
)

set (SFML_DIR "C:/SFML/")
find_package (SFML REQUIRED system window graphics network audio)

include_directories(${SFML_INCLUDE_DIR})

set (SFML_LIBRARIES sfml-audio sfml-graphics sfml-network sfml-system)

#we add the executable of the program
add_executable (game ${SOURCE_FILES})
target_link_libraries (game ${SFML_LIBRARIES})
