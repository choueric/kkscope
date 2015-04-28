project (husky)

find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)
find_package (BISON)
find_package (FLEX)

include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
add_definitions(-DTESTCASE)

MESSAGE(STATUS "BINARY dir is : " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "SOURCE dir is : " ${PROJECT_SOURCE_DIR})

set (husky_FORMS
    ${PROJECT_SOURCE_DIR}/ui/makelayout.ui
    ${PROJECT_SOURCE_DIR}/ui/calltreelayout.ui
    ${PROJECT_SOURCE_DIR}/ui/cscopemsglayout.ui
    ${PROJECT_SOURCE_DIR}/ui/graphpreflayout.ui
    ${PROJECT_SOURCE_DIR}/ui/prefcolorlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/preffontlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/prefoptlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/preffrontendlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/querywidgetlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/openprojectlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/queryviewlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/autocompletionlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/newprojectlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/searchresultslayout.ui
    ${PROJECT_SOURCE_DIR}/ui/scanprogresslayout.ui
    ${PROJECT_SOURCE_DIR}/ui/fileviewlayout.ui
    ${PROJECT_SOURCE_DIR}/ui/projectfileslayout.ui
    ${PROJECT_SOURCE_DIR}/ui/welcomedlg.ui
    ${PROJECT_SOURCE_DIR}/ui/symbollayout.ui
    ${PROJECT_SOURCE_DIR}/ui/bookmarkslayout.ui)

QT4_WRAP_UI(husky_FORMS_HEADERS
    ${husky_FORMS})

set (husky_SRCS 
    #${PROJECT_SOURCE_DIR}/symbolcompletion.cpp
    ${PROJECT_SOURCE_DIR}/main.cpp 
    ${PROJECT_SOURCE_DIR}/kscope.cpp 
    ${PROJECT_SOURCE_DIR}/projectmanager.cpp
    ${PROJECT_SOURCE_DIR}/project.cpp
    ${PROJECT_SOURCE_DIR}/projectbase.cpp
    ${PROJECT_SOURCE_DIR}/projectfilesdlg.cpp
    ${PROJECT_SOURCE_DIR}/scanprogressdlg.cpp
    ${PROJECT_SOURCE_DIR}/dirscanner.cpp
    ${PROJECT_SOURCE_DIR}/makedlg.cpp
    ${PROJECT_SOURCE_DIR}/makefrontend.cpp
    ${PROJECT_SOURCE_DIR}/calltreedlg.cpp
    ${PROJECT_SOURCE_DIR}/calltreemanager.cpp
    ${PROJECT_SOURCE_DIR}/symboldlg.cpp
    ${PROJECT_SOURCE_DIR}/treewidget.cpp
    ${PROJECT_SOURCE_DIR}/editortabs.cpp
    ${PROJECT_SOURCE_DIR}/editorpage.cpp
    ${PROJECT_SOURCE_DIR}/editormanager.cpp
    ${PROJECT_SOURCE_DIR}/kscopeactions.cpp
    ${PROJECT_SOURCE_DIR}/cscopemsgdlg.cpp
    ${PROJECT_SOURCE_DIR}/dotfrontend.cpp
    ${PROJECT_SOURCE_DIR}/graphnode.cpp
    ${PROJECT_SOURCE_DIR}/graphedge.cpp
    ${PROJECT_SOURCE_DIR}/graphwidget.cpp
    ${PROJECT_SOURCE_DIR}/graphprefdlg.cpp
    ${PROJECT_SOURCE_DIR}/encoder.cpp
    ${PROJECT_SOURCE_DIR}/progressdlg.cpp
    ${PROJECT_SOURCE_DIR}/prefcolor.cpp
    ${PROJECT_SOURCE_DIR}/preffont.cpp
    ${PROJECT_SOURCE_DIR}/prefopt.cpp
    ${PROJECT_SOURCE_DIR}/preffrontend.cpp
    ${PROJECT_SOURCE_DIR}/preferencesdlg.cpp
    ${PROJECT_SOURCE_DIR}/querywidget.cpp
    ${PROJECT_SOURCE_DIR}/querypagebase.cpp
    ${PROJECT_SOURCE_DIR}/historyview.cpp
    ${PROJECT_SOURCE_DIR}/historypage.cpp
    ${PROJECT_SOURCE_DIR}/tabwidget.cpp
    ${PROJECT_SOURCE_DIR}/querypage.cpp
    ${PROJECT_SOURCE_DIR}/openprojectdlg.cpp
    ${PROJECT_SOURCE_DIR}/newprojectdlg.cpp
    ${PROJECT_SOURCE_DIR}/bookmarksdlg.cpp
    ${PROJECT_SOURCE_DIR}/queryview.cpp
    ${PROJECT_SOURCE_DIR}/queryresultsmenu.cpp
    ${PROJECT_SOURCE_DIR}/queryviewdriver.cpp
    ${PROJECT_SOURCE_DIR}/queryviewdlg.cpp
    ${PROJECT_SOURCE_DIR}/searchresultsdlg.cpp
    ${PROJECT_SOURCE_DIR}/frontend.cpp
    ${PROJECT_SOURCE_DIR}/ctagsfrontend.cpp
    ${PROJECT_SOURCE_DIR}/ctagslist.cpp
    ${PROJECT_SOURCE_DIR}/cscopefrontend.cpp
    ${PROJECT_SOURCE_DIR}/configfrontend.cpp
    ${PROJECT_SOURCE_DIR}/fileview.cpp
    ${PROJECT_SOURCE_DIR}/filelist.cpp   # to remove
    ${PROJECT_SOURCE_DIR}/filelistwidget.cpp
    ${PROJECT_SOURCE_DIR}/stringlistmodel.cpp
    ${PROJECT_SOURCE_DIR}/kscopeconfig.cpp
    ${PROJECT_SOURCE_DIR}/kscopepixmaps.cpp
    ${PROJECT_SOURCE_DIR}/searchlist.cpp   # to remove
    ${PROJECT_SOURCE_DIR}/searchlistview.cpp
    )

FLEX_TARGET(dotscan ${PROJECT_SOURCE_DIR}/yacc/dotscan.lpp ${PROJECT_BINARY_DIR}/dotscan.cpp)
BISON_TARGET(dotparse ${PROJECT_SOURCE_DIR}/yacc/dotparse.ypp ${PROJECT_BINARY_DIR}/dotparse.cpp)
add_flex_bison_dependency(dotscan dotparse)

kde4_add_executable (husky ${husky_SRCS} ${husky_FORMS_HEADERS} ${BISON_dotparse_OUTPUTS} ${FLEX_dotscan_OUTPUTS})
target_link_libraries (husky ${KDE4_KDEUI_LIBS}
    ${KDE4_KPARTS_LIBS}
    ${KDE4_KFILE_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS})
install(TARGETS husky ${INSTALL_TARGETS_DEFAULT_ARGS})

# see techbase.kde.org/Development/CMake/Addons_for_KDE for more libraries
