project (husky_test)
find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)
include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
add_definitions(-DTESTCASE)

set (husky_FORMS
    ../../ui/searchresultslayout.ui
    ../../ui/queryviewlayout.ui)
QT4_WRAP_UI(husky_FORMS_HEADERS
    ${husky_FORMS})

set (husky_SRCS 
    main.cpp 
    mainwin.cpp
    ../../editormanager.cpp
    ../../editortabs.cpp
    ../../tabwidget.cpp
    ../../queryview.cpp
    ../../queryviewdlg.cpp
    ../../queryviewdriver.cpp
    ../../queryresultsmenu.cpp
    ../../searchresultsdlg.cpp
    #../../projectmanager.cpp
    ../../editorpage.cpp
    ../../projectbase.cpp
    ../../kscopeconfig.cpp
    ../../cscopefrontend.cpp
    ../../configfrontend.cpp
    ../../frontend.cpp
    ../../ctagslist.cpp
    ../../ctagsfrontend.cpp
    ../../kscopepixmaps.cpp
    ../../searchlist.cpp)
kde4_add_executable (husky_test ${husky_SRCS} ${husky_FORMS_HEADERS})
target_link_libraries (husky_test ${KDE4_KDEUI_LIBS}
    ${KDE4_KPARTS_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS})
install(TARGETS husky_test ${INSTALL_TARGETS_DEFAULT_ARGS})
