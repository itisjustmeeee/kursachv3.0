cmake_minimum_required(VERSION 3.19)
project(kursach_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.9.0 COMPONENTS Core Widgets Concurrent REQUIRED)

find_package(Git)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    mainwindow.cpp
    textinputwindow.cpp
    fileinputwindow.cpp
    instructionwindow.cpp
    wordanalyzer.cpp
    analysisworker.cpp
    resultcache.cpp
    analytics.cpp
    wordgraph.cpp
)

set(HEADERS
    mainwindow.h
    textinputwindow.h
    fileinputwindow.h
    instructionwindow.h
    wordanalyzer.h
    analysisworker.h
    resultcache.h
    analytics.h
    wordgraph.h
)

set(UI_FILES
    mainwindow.ui
    textinputwindow.ui
    fileinputwindow.ui
    instructionwindow.ui
)

set(RESOURCE_FILES
    resources.qrc
)

if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --always
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_COMMIT_HASH "unknown")
    set(GIT_VERSION "unknown")
endif()

add_definitions(-DGIT_COMMIT_HASH="${GIT_COMMIT_HASH}")
add_definitions(-DGIT_VERSION="${GIT_VERSION}")

qt_add_executable(kursach_2
    WIN32
    ${SOURCES}
    ${HEADERS}
    ${UI_FILES}
    ${RESOURCE_FILES}
)

target_link_libraries(kursach_2
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::Concurrent
)

target_include_directories(kursach_2 PRIVATE ${CMAKE_SOURCE_DIR})

set_target_properties(kursach_2 PROPERTIES
    WIN32_EXECUTABLE ON
)

include(GNUInstallDirs)
install(TARGETS kursach_2
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET kursach_2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

add_custom_target(tag
    COMMAND ${GIT_EXECUTABLE} tag -a v${GIT_VERSION} -m "Release ${GIT_VERSION}"
    COMMAND ${GIT_EXECUTABLE} push origin v${GIT_VERSION}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Creating and pushing Git tag"
)
