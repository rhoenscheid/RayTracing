add_library(RayTracer STATIC ImageUtils.cpp VectorUtils.cpp Ray.cpp Plane.cpp Rendering.cpp Sphere.cpp Object.cpp)
target_include_directories(RayTracer PUBLIC ${CMAKE_SOURCE_DIR}/include)