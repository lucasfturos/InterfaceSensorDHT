# -------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16)

project(InterfaceSensorDHT
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4
    COMPONENTS
    Quick
    Core
    SerialPort
    REQUIRED
)

qt_standard_project_setup()

set(PROJECT_HEADERS
    src/SensorDHT/sensordht.hpp
    src/SearchDevice/searchdevice.hpp
    src/SerialCommunication/serialcomm.hpp
)

set(PROJECT_SOURCES
    src/SensorDHT/sensordht.cpp
    src/SearchDevice/searchdevice.cpp
    src/SerialCommunication/serialcomm.cpp
    src/main.cpp
)

set(PROJECT_QML
    # Window
    qml/Home.qml
    qml/Main.qml
    # View
    qml/view/Radio.qml
    qml/view/Serial.qml
    qml/view/Server.qml
)

qt_add_executable(appInterfaceSensorDHT
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

qt_add_qml_module(appInterfaceSensorDHT
    URI InterfaceSensorDHT
    VERSION 1.0
    RESOURCES
    QML_FILES ${PROJECT_QML}
)

set_target_properties(appInterfaceSensorDHT PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(appInterfaceSensorDHT
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    PRIVATE Qt6::SerialPort
)

include(GNUInstallDirs)
install(TARGETS appInterfaceSensorDHT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(docs)

# -------------------------------------------------------------------
