cmake_minimum_required(VERSION 3.19)
project(kursach_2 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(kursach_2
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    textinputwindow.h textinputwindow.cpp textinputwindow.ui
    fileinputwindow.h fileinputwindow.cpp fileinputwindow.ui
    instructionwindow.h instructionwindow.cpp instructionwindow.ui
    wordanalyzer.h wordanalyzer.cpp
    analysisworker.h analysisworker.cpp
    resultcache.h resultcache.cpp
    analytics.h analytics.cpp

    wordgraph.h wordgraph.cpp
    resources.qrc
)

qt6_add_resources(kursach_2 "resources"
    PREFIX "/"
    FILES MaterialDark.qss
)

target_link_libraries(kursach_2
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS kursach_2
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET kursach_2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
