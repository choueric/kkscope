project (husky_test)
find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)
include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
include_directories (${PROJECT_SOURCE_DIR}/../../src)
add_definitions(-DTESTCASE)

set (husky_FORMS
    ../../src/ui/graphpreflayout.ui

    ../../src/ui/prefcolorlayout.ui
    ../../src/ui/preffontlayout.ui
    ../../src/ui/prefoptlayout.ui
    ../../src/ui/preffrontendlayout.ui

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
     ../../src/dotfrontend.cpp
     ../../src/graphnode.cpp
     ../../src/graphedge.cpp
     ../../src/graphwidget.cpp
     ../../src/graphprefdlg.cpp
     ../../src/encoder.cpp
     ../../src/progressdlg.cpp

	 ../../src/stringlistmodel.cpp

    ../../src/prefcolor.cpp
    ../../src/preffont.cpp
    ../../src/prefopt.cpp
    ../../src/preffrontend.cpp
    ../../src/preferencesdlg.cpp

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
    ../../src/ctagsfrontend.cpp
    ../../src/cscopefrontend.cpp
    ../../src/configfrontend.cpp
    ../../src/projectbase.cpp
    ../../src/fileview.cpp
    ../../src/filelistwidget.cpp
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
