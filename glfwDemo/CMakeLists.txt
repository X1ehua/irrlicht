cmake_minimum_required(VERSION 3.10)
project(glfwDemo)

find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(ZLIB REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

set(PARENT_APP_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# include_directories($ENV{HOME}/irrlichtmt/include)

set(link_libs
    "-framework Cocoa -framework IOKit -framework CoreFoundation"
	${ZLIB_LIBRARY}
	${JPEG_LIBRARY}
	${PNG_LIBRARY}
    ${OPENGL_LIBRARIES}
    /opt/homebrew/Cellar/glfw/3.3.5/lib/libglfw.dylib
    ${FREETYPE_LIBRARY}
    # $ENV{HOME}/minetest/build/lib/irrlichtmt/lib/OSX/Debug/libIrrlichtMt.a
	IrrlichtMt::IrrlichtMt
)
# message( $ENV{HOME}/irrlichtmt/lib/OSX/libIrrlichtMt.a )

set(exec_name "glfwDemo")

add_subdirectory("lib/irrlichtmt" EXCLUDE_FROM_ALL)

# file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/${exname}/*.cpp")
file(GLOB includes "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h")
add_executable(${exec_name}
	# ${sources}
	${includes}
	main.cpp
)
target_link_libraries(${exec_name} ${link_libs})

# target_include_directories(${exname} PRIVATE
# 	${CMAKE_SOURCE_DIR}/include
# 	${CMAKE_CURRENT_SOURCE_DIR}/${exname}
# )
