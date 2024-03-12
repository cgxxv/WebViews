cmake_minimum_required(VERSION 3.5)

project(ChatGPTs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets WebEngineWidgets)

set(PROJECT_SOURCES
        ChatGPTs.icns
        src/main.cpp
        src/mainwindow.h src/mainwindow.cpp
        resource.qrc
        src/mainwindow.ui
        src/util.h src/util.cpp
        src/webengineview.h src/webengineview.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ChatGPTs
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ChatGPTs APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ChatGPTs SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ChatGPTs
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ChatGPTs PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

set_target_properties(ChatGPTs PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.github.cgxxv.ChatGPTs
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_BUNDLE_IDENTIFIER com.cgxxv.ChatGPTs
    MACOSX_BUNDLE_ICON_FILE ChatGPTs.icns
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
set_source_files_properties(ChatGPTs.icns PROPERTIES
           MACOSX_PACKAGE_LOCATION "Resources")

include(GNUInstallDirs)
install(TARGETS ChatGPTs
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ChatGPTs)
endif()
