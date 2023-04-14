cmake_minimum_required(VERSION 3.16)
project (App)


INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# find_package(SDL2 REQUIRED)
# find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})

file(GLOB_RECURSE APP_SRCS src/*.cpp)
file(GLOB_RECURSE APP_HDRS src/*.h)

add_executable(App ${APP_SRCS} ${APP_HDRS})

target_include_directories(App PUBLIC include)

target_link_libraries(App ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARIES})