cmake_minimum_required(VERSION 3.5)

project(SmartBilliard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)
set(OpenCV_DIR "F:/Qt_Opencv")
# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Add OpenCV headers location to your include paths
include_directories(${OpenCV_INCLUDE_DIRS})
# HIK MVS SDK
include_directories("${PROJECT_SOURCE_DIR}/HIK/Includes")
link_directories("${PROJECT_SOURCE_DIR}/HIK/Libraries/win64")
# OCR
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartBilliard
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        login.h
        login.cpp
        login.ui
        user.h
        user.cpp
        global_wjl.h
        global_wjl.cpp
        sqlhelper.h
        sqlhelper.cpp
        res.qrc
        hikcamera.h
        hikcamera.cpp
        logo.rc
        playcontrol.h playcontrol.cpp
        playcontrol.ui
        piclabel.h piclabel.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartBilliard APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartBilliard SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartBilliard
            ${PROJECT_SOURCES}
        )
    endif()
endif()
target_link_libraries(SmartBilliard PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql ${OpenCV_LIBS} "MvCameraControl")
set_target_properties(SmartBilliard PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SmartBilliard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartBilliard)
endif()
