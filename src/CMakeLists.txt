project (kscope)

find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)

include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
add_definitions(-DTESTCASE)

set (CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

MESSAGE(STATUS "BINARY dir is : " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "SOURCE dir is : " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "output directory is : " ${CMAKE_BINARY_DIR})

set (kscope_FORMS
    ${PROJECT_SOURCE_DIR}/ui/makelayout.ui
    ${PROJECT_SOURCE_DIR}/ui/cscopemsglayout.ui
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
    ${PROJECT_SOURCE_DIR}/ui/bookmarkslayout.ui
    )

QT4_WRAP_UI(kscope_FORMS_HEADERS ${kscope_FORMS})

aux_source_directory(${PROJECT_SOURCE_DIR} kscope_SRCS)

kde4_add_ui_files(kscope_SRCS)

kde4_add_executable (kscope ${kscope_SRCS} ${kscope_FORMS_HEADERS})

# see techbase.kde.org/Development/CMake/Addons_for_KDE for more libraries
target_link_libraries (kscope ${KDE4_KDEUI_LIBS}
    ${KDE4_KPARTS_LIBS}
    ${KDE4_KFILE_LIBS}
    ${KDE4_KTEXTEDITOR_LIBS})

MESSAGE(STATUS "bin dir is : " ${INSTALL_TARGETS_DEFAULT_ARGS})
MESSAGE(STATUS "ui.rc dir is : " ${DATA_INSTALL_DIR})
MESSAGE(STATUS "icon install dir is : " ${ICON_INSTALL_DIR})

install(TARGETS kscope ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${PROJECT_SOURCE_DIR}/ui/kscopeui.rc DESTINATION ${DATA_INSTALL_DIR}/kscope)
kde4_install_icons(${PROJECT_SOURCE_DIR}/ui/pics ${ICON_INSTALL_DIR})
