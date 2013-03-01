cmake_minimum_required (VERSION 2.6)
project (mobi2epub)

find_package(Boost)



add_subdirectory(epub)
add_subdirectory(mobi)

set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(libs ${libs} boost_program_options)
set(libs ${libs} boost_filesystem)
set(libs ${libs} boost_system)
set(libs ${libs} tidy)
set(libs ${libs} epub_functions)
set(libs ${libs} mobi_functions)
#set(libs ${libs} mobi_handler)

add_executable(mobi2epub main.cpp)
target_link_libraries(mobi2epub ${libs} )

