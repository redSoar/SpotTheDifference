cmake_minimum_required(VERSION 3.22)
project(SpotTheDifference)

set(CMAKE_CXX_STANDARD 17)

# Add the path to the CIMG library header
include_directories(lib/cimg)

add_executable(SpotTheDifference main.cpp
        lib/src/imageClass.cpp
        lib/src/pixelClass.cpp)

# Link against the required libraries
target_link_libraries(SpotTheDifference m pthread X11)
target_link_libraries(SpotTheDifference m pthread X11 png)
target_link_libraries(SpotTheDifference m pthread X11 jpeg)



# Set compiler flags for CIMG
target_compile_options(SpotTheDifference PRIVATE
        -Dcimg_display=1  # Disable display capabilities if not available
        -Dcimg_use_png    # Enable PNG support
        -Dcimg_use_jpeg   # Enable JPEG support
        # Add other necessary flags based on your requirements
)