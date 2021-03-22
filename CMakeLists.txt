cmake_minimum_required(VERSION 3.13)
project(spc2ParticleFluidMovie)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include/ /usr/local/include/freetype2/)
link_directories(/usr/local/lib)
#set(CMAKE_OSX_SYSROOT /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk)

add_executable(spc2ParticleFluidMovie
        main.cpp
        SimulationModel.cpp SimulationModel.hpp
        ParameterContainer.cpp ParameterContainer.hpp
        Definitions.hpp
        Renderer.cpp Renderer.hpp
        ScreenshotHandler.cpp ScreenshotHandler.hpp)

file(GLOB LIBRARIES "/usr/local/lib/libGLEW.1.13.0.dylib"
        "/usr/local/lib/libglfw.3.1.dylib"
        "/usr/local/lib/libpng16.16.dylib"
        "/usr/local/lib/libfreetype.a"
        "/usr/local/opt/bzip2/lib/libbz2.a"
        "/usr/local/opt/zlib/lib/libz.a")
message("LIBRARIES = ${LIBRARIES}")
target_link_libraries(spc2ParticleFluidMovie ${LIBRARIES})

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-framework OpenGL" COMPILER_SUPPORTS_FRAMEWORK_OPENGL)
if (COMPILER_SUPPORTS_FRAMEWORK_OPENGL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL")
endif ()

#set(GCC_COVERAGE_COMPILE_FLAGS "-march=native -flto -O3")
#set(GCC_COVERAGE_LINK_FLAGS "")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")