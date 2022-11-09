cmake_minimum_required(VERSION 3.22)

project(drone-monitor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    3DCore
    3DRender
    3DInput
    3DLogic
    3DExtras
    3DAnimation
    Network
)
qt_standard_project_setup()

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(drone-monitor
    ${SOURCES}
    ${HEADERS}
)

include_directories(include)

target_link_libraries(drone-monitor PRIVATE
    Qt6::Widgets
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DLogic
    Qt6::3DExtras
    Qt6::Network
    Qt6::3DAnimation
)
