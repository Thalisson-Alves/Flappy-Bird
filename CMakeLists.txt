#sets up the minimum version of cmake
cmake_minimum_required(VERSION 3.9)

#how the project will be called
project(FlappyBirdAI)

#set the C++ standard to be used
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")

#set source files
set(SOURCE_FILES
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

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_LIBRARIES sfml-audio sfml-graphics sfml-network sfml-system)

find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    if (NOT SFML_INCLUDE_DIR)
        set(SFML_INCLUDE_DIR ${SFML_DIR}/../../../include)
    endif ()

    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif ()
