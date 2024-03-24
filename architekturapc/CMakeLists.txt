cmake_minimum_required(VERSION 3.0)
project(blok2)

# Find ncurses package
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add your source file
add_executable(blok2 blok2.c)

# Link against ncurses library
target_link_libraries(blok2 ${CURSES_LIBRARIES})
