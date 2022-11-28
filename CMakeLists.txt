cmake_minimum_required(VERSION 3.22)

project(drone-monitor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)

option(CUSTOM_STYLESHEET "Use custom stylecheet" ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    3DCore
    3DRender
    3DInput
    3DLogic
    3DExtras
    3DAnimation
    Network
    SerialPort
)
qt_standard_project_setup()

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

if (CUSTOM_STYLESHEET)
  add_compile_definitions(USE_CUSTOM_STYLESHEET)
endif()

add_executable(drone-monitor
    ${SOURCES}
    ${HEADERS}
    resources.qrc
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
    Qt6::SerialPort
)

set_target_properties(drone-monitor PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

include(GNUInstallDirs)

install(TARGETS drone-monitor
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES LICENSE
    DESTINATION ${CMAKE_INSTALL_DOCDIR}
)

qt_generate_deploy_app_script(
    TARGET drone-monitor
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})

set(PACKAGE_NAME "Drone Monitor")

set(CPACK_PACKAGE_VENDOR "Romain Chardiny and Robin Perdreau")
set(CPACK_PACKAGE_CONTACT "Romain Chardiny <romain.chardiny@gmail.com>")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "drone-monitor")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_EXECUTABLES "drone-monitor;Drone Monitor")

set(CPACK_NSIS_DISPLAY_NAME ${PACKAGE_NAME})
set(CPACK_NSIS_PACKAGE_NAME ${PACKAGE_NAME})
set(CPACK_NSIS_MANIFEST_DPI_AWARE ON)

set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt6widgets6, libqt63dcore6, libqt63dextras6, libqt63dinput6, libqt63drender6, libqt63danimation6, libqt6network6, libqt6serialport6")

include(CPack)
