cmake_minimum_required(VERSION 3.5)

project(QDevTool VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_PREFIX_PATH /Users/liuhaoran/Qt/5.15.2/macos/)
set(CMAKE_PREFIX_PATH /Users/liuhaoran/Qt/6.2.1/macos/lib/cmake)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES ../translations/QDevTool_zh_CN.ts)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
        ../qss.qrc
        QCodeExport/qcodeexport.cpp
        QCodeExport/qcodeexport.h
        QCodeExport/qcodeexport.ui
        )
#set(CMAKE_BUILD_TYPE Debug)
#set (CMAKE_CXX_STANDARD 11)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 COMPONENTS Core5Compat REQUIRED)
    qt_add_executable(QDevTool
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET QDevTool APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

else ()
    if (ANDROID)
        add_library(QDevTool SHARED
                ${PROJECT_SOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(QDevTool
                ${PROJECT_SOURCES}
                )
    endif ()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

target_link_libraries(QDevTool PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(QDevTool PUBLIC Qt6::Core5Compat)
set_target_properties(QDevTool PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER lhrsite.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QDevTool)
endif ()


#install(
#        TARGETS QDevTool
#        DESTINATION ${PROJECT_BINARY_DIR}
#)
#install(TARGETS QDevTool DESTINATION ${PROJECT_BINARY_DIR}/lib)
#install(
#        DIRECTORY ${PROJECT_BINARY_DIR}/resources/
#        DESTINATION resources
#)
#install(
#        DIRECTORY ${PROJECT_BINARY_DIR}/config/
#        DESTINATION config
#)