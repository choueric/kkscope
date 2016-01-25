project (husky_test)
find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)
include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
include_directories (${PROJECT_SOURCE_DIR}/../../src)

MESSAGE(STATUS "source dir is : " ${PROJECT_SOURCE_DIR})

add_definitions(-DTESTCASE)

set (husky_FORMS
    ../../src/ui/searchresultslayout.ui
    ../../src/ui/querywidgetlayout.ui
    ../../src/ui/openprojectlayout.ui
    ../../src/ui/queryviewlayout.ui
    ../../src/ui/fileviewlayout.ui
    ../../src/ui/bookmarkslayout.ui)
QT4_WRAP_UI(husky_FORMS_HEADERS
    ${husky_FORMS})

set (husky_SRCS 
    main.cpp 
    mainwin.cpp
    ../../src/filelistwidget.cpp
    ../../src/bookmarksdlg.cpp
    ../../src/queryview.cpp
    ../../src/queryresultsmenu.cpp
    ../../src/queryviewdriver.cpp
    ../../src/queryviewdlg.cpp
    ../../src/searchresultsdlg.cpp
    ../../src/frontend.cpp
    ../../src/ctagsfrontend.cpp
	 ../../src/stringlistmodel.cpp
    ../../src/cscopefrontend.cpp
    ../../src/configfrontend.cpp
    ../../src/projectbase.cpp
    ../../src/fileview.cpp
    ../../src/filelistwidget.cpp
    ../../src/kscopeconfig.cpp
    ../../src/kscopepixmaps.cpp
    ../../src/searchlistview.cpp)

kde4_add_executable (husky_test ${husky_SRCS} ${husky_FORMS_HEADERS})
target_link_libraries (husky_test ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${QT_LIBRARIES})
install(TARGETS husky_test ${INSTALL_TARGETS_DEFAULT_ARGS})
