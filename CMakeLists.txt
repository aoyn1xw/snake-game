cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
set(SOURCES
    src/main.cpp
    src/game/SnakeGame.cpp
    src/cli/CLIRenderer.cpp
    src/gui/GUIRenderer.cpp
)

add_executable(snake-game ${SOURCES})

# Platform-specific libraries for CLI
if(WIN32)
    # Windows doesn't need additional libraries for console I/O
else()
    # Unix/Linux systems
    target_link_libraries(snake-game)
endif()

# Try to find SFML
find_package(PkgConfig)
if(PkgConfig_FOUND)
    pkg_check_modules(SFML sfml-all)
endif()

# Modern CMake SFML detection (SFML 2.5+)
if(NOT SFML_FOUND)
    find_package(SFML 2.5 COMPONENTS graphics window system QUIET)
    if(SFML_FOUND)
        set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system)
    endif()
endif()

# Try SFML 3.x
if(NOT SFML_FOUND)
    find_package(SFML 3 COMPONENTS Graphics Window System QUIET)
    if(SFML_FOUND)
        set(SFML_LIBRARIES SFML::Graphics SFML::Window SFML::System)
    endif()
endif()

# Legacy SFML detection for older systems
if(NOT SFML_FOUND)
    find_path(SFML_INCLUDE_DIR SFML/Graphics.hpp
        PATHS
        /usr/include
        /usr/local/include
        /opt/homebrew/include
        "C:/SFML/include"
        ${CMAKE_PREFIX_PATH}/include
    )
    
    find_library(SFML_GRAPHICS_LIBRARY
        NAMES sfml-graphics
        PATHS
        /usr/lib
        /usr/local/lib
        /opt/homebrew/lib
        "C:/SFML/lib"
        ${CMAKE_PREFIX_PATH}/lib
    )
    
    find_library(SFML_WINDOW_LIBRARY
        NAMES sfml-window
        PATHS
        /usr/lib
        /usr/local/lib
        /opt/homebrew/lib
        "C:/SFML/lib"
        ${CMAKE_PREFIX_PATH}/lib
    )
    
    find_library(SFML_SYSTEM_LIBRARY
        NAMES sfml-system
        PATHS
        /usr/lib
        /usr/local/lib
        /opt/homebrew/lib
        "C:/SFML/lib"
        ${CMAKE_PREFIX_PATH}/lib
    )
    
    if(SFML_INCLUDE_DIR AND SFML_GRAPHICS_LIBRARY AND SFML_WINDOW_LIBRARY AND SFML_SYSTEM_LIBRARY)
        set(SFML_FOUND TRUE)
        set(SFML_LIBRARIES ${SFML_GRAPHICS_LIBRARY} ${SFML_WINDOW_LIBRARY} ${SFML_SYSTEM_LIBRARY})
        set(SFML_INCLUDE_DIRS ${SFML_INCLUDE_DIR})
    endif()
endif()

# Configure based on SFML availability
if(SFML_FOUND)
    message(STATUS "SFML found - enabling GUI mode")
    target_compile_definitions(snake-game PRIVATE ENABLE_GUI)
    target_include_directories(snake-game PRIVATE ${SFML_INCLUDE_DIRS})
    target_link_libraries(snake-game ${SFML_LIBRARIES})
    
    # On Windows, we might need additional system libraries
    if(WIN32)
        target_link_libraries(snake-game opengl32 winmm gdi32)
    endif()
else()
    message(STATUS "SFML not found - CLI mode only")
    message(STATUS "To enable GUI mode, install SFML:")
    message(STATUS "  Ubuntu/Debian: sudo apt-get install libsfml-dev")
    message(STATUS "  Fedora/RHEL:   sudo dnf install SFML-devel")
    message(STATUS "  macOS:         brew install sfml")
    message(STATUS "  Windows:       Download from https://www.sfml-dev.org/")
endif()

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(snake-game PRIVATE -Wall -Wextra)
endif()

# Installation
install(TARGETS snake-game DESTINATION bin)

# Print build information
message(STATUS "Build configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  GUI Support: ${SFML_FOUND}")