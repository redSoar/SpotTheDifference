cmake_minimum_required(VERSION 3.22)
project(SpotTheDifference)

set(CMAKE_CXX_STANDARD 17)

# find SDL libraries
find_package(SDL2 REQUIRED)

# Add the path to the CIMG library header
include_directories(lib/cimg)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SpotTheDifference main.cpp
        lib/src/imageClass.cpp
        lib/include/imageClass.h
        lib/src/pixelClass.cpp
        lib/include/pixelClass.h
        lib/src/GameController.cpp
        lib/include/GameController.h
        lib/include/GameStage.h)

# Link against the required libraries
target_link_libraries(SpotTheDifference m pthread X11)
target_link_libraries(SpotTheDifference m pthread X11 png)
target_link_libraries(SpotTheDifference m pthread X11 jpeg)
target_link_libraries(SpotTheDifference ${SDL2_LIBRARIES})



# Set compiler flags for CIMG
target_compile_options(SpotTheDifference PRIVATE
        -Dcimg_display=1  # Disable display capabilities if not available
        -Dcimg_use_png    # Enable PNG support
        -Dcimg_use_jpeg   # Enable JPEG support
        # Add other necessary flags based on your requirements
)