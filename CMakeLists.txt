cmake_minimum_required(VERSION 3.16)

project(AvtoPoshuk VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appAvtoPoshuk
    main.cpp
)

qt_add_qml_module(appAvtoPoshuk
    URI AvtoPoshuk
    VERSION 1.0
    QML_FILES
        Main.qml
        LoginPage.qml
        MainListPage.qml
        AddCarPage.qml
        AccountPage.qml
        MyAdsPage.qml
    SOURCES
        databasemanager.h
        databasemanager.cpp
        car.h
        car.cpp
        authviewmodel.h
        authviewmodel.cpp
        carlistviewmodel.h
        carlistviewmodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAvtoPoshuk PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAvtoPoshuk
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAvtoPoshuk
    PRIVATE Qt6::Quick Qt6::Network
)

install(TARGETS appAvtoPoshuk
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
