cmake_minimum_required(VERSION 3.5)

project(Netetris LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

set (HEADERS
    )

set (SOURCES
    main.cpp
    )

set (RESOURCES
    qml.qrc
    )

add_executable(Netetris ${HEADERS} ${SOURCES} ${RESOURCES})

target_compile_definitions(Netetris
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Netetris
    PRIVATE Qt5::Core Qt5::Quick)
