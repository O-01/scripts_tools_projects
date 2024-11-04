cmake_minimum_required(VERSION 3.5)

project(netrunner_card_finder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# set(CURL_LIBRARY "-lcurl")
# find_package(CURL REQUIRED)
# if(CURL_FOUND)
#     message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
#     message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
#     message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")
#     include_directories(${CURL_INCLUDE_DIRS})
#     target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
# else()
#     message(FATAL_ERROR "Could not find CURLLL")
# endif()

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        include/mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(netrunner_card_finder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET netrunner_card_finder APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(netrunner_card_finder SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(netrunner_card_finder
            ${PROJECT_SOURCES}
            cards.json
            simdjson.cpp
            include/simdjson.h

        )
    endif()
endif()

target_link_libraries(netrunner_card_finder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${CURL_LIBRARIES})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.netrunner_card_finder)
endif()
set_target_properties(netrunner_card_finder PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS netrunner_card_finder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(netrunner_card_finder)
endif()
