project (husky_test)
find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)
include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
include_directories (${PROJECT_SOURCE_DIR}/../../src)
add_definitions(-DTESTCASE)

set (CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")

set (husky_FORMS
    ../../src/ui/querywidgetlayout.ui

    ../../src/ui/openprojectlayout.ui
    ../../src/ui/queryviewlayout.ui
    ../../src/ui/autocompletionlayout.ui
    ../../src/ui/newprojectlayout.ui
    ../../src/ui/searchresultslayout.ui
    ../../src/ui/fileviewlayout.ui
    ../../src/ui/bookmarkslayout.ui)
QT4_WRAP_UI(husky_FORMS_HEADERS
    ${husky_FORMS})

set (husky_SRCS 
    ../../src/querywidget.cpp
    ../../src/querypagebase.cpp
    ../../src/historyview.cpp
    ../../src/historypage.cpp
    ../../src/tabwidget.cpp
    ../../src/querypage.cpp

    ../../src/openprojectdlg.cpp
    ../../src/newprojectdlg.cpp
    main.cpp 
    mainwin.cpp
    ../../src/bookmarksdlg.cpp
    ../../src/queryview.cpp
    ../../src/queryresultsmenu.cpp
    ../../src/queryviewdriver.cpp
    ../../src/queryviewdlg.cpp
    ../../src/searchresultsdlg.cpp
    ../../src/frontend.cpp
    ../../src/cscopefrontend.cpp
    ../../src/configfrontend.cpp
    ../../src/projectbase.cpp
    ../../src/fileview.cpp
    ../../src/filelistwidget.cpp
    ../../src/stringlistmodel.cpp
    ../../src/kscopeconfig.cpp
    ../../src/kscopepixmaps.cpp
    ../../src/searchlistview.cpp)
kde4_add_executable (husky_test ${husky_SRCS} ${husky_FORMS_HEADERS})
target_link_libraries (husky_test ${KDE4_KDEUI_LIBS}
    ${KDE4_KPARTS_LIBS}
    ${KDE4_KFILE_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS})
install(TARGETS husky_test ${INSTALL_TARGETS_DEFAULT_ARGS})

# see techbase.kde.org/Development/CMake/Addons_for_KDE for more libraries
