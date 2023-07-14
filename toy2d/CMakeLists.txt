file(GLOB_RECURSE src CONFIGURE_DEPENDS src/*.cpp include/*.h)
add_library(toy2d STATIC ${src})
target_include_directories(toy2d PUBLIC include)
