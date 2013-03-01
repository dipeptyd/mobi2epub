add_definitions(-std=gnu++0x)
add_library(mobi_functions mobi.cpp mobi_headers_handler.cpp  mobi_headers.cpp compression/compression.cpp)
#add_library(mobi_handler  mobi_headers_handler.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
