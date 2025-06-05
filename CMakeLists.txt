cmake_minimum_required(VERSION 3.5)
project(ils LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Sql Network REQUIRED)

set(SOURCES
    main.cpp
    welcome.cpp
    mainwindow.cpp
    books.cpp
    addbook.cpp
    issuebook.cpp
    admin.cpp
    members.cpp
    connectdb.cpp
    wizards/editbookwizard.cpp
    wizards/addcopywizard.cpp
    wizards/returnbookwizarad.cpp
    wizards/summarywizard.cpp
    wizards/addbookwizard.cpp
    wizards/bookinfoonline.cpp
    wizards/addmemberwizard.cpp
    wizards/issuebookwizard.cpp
)

qt5_add_resources(QRC_SOURCES resources.qrc)

add_executable(${PROJECT_NAME} ${SOURCES} ${QRC_SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Sql Qt5::Network)
