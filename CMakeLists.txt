cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_check_modules(HANGUL REQUIRED libhangul)
pkg_check_modules(NCURSES REQUIRED ncurses)

project(hangultaja)

file(GLOB CXX_SOURCES "src/*.cpp")
file(GLOB CXX_HEADERS "src/*.hpp")

add_executable(hangultaja ${CXX_SOURCES} ${CXX_HEADERS})

target_include_directories(hangultaja PRIVATE ${HANGUL_INCLUDE_DIRS} ${NCURSES_INCLUDE_DIRS})
target_link_libraries(hangultaja PRIVATE ${HANGUL_LIBRARIES} ${NCURSES_LIBRARIES})