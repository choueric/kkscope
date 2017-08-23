project (kscope)

set(ENV{QT_SELECT} 4)

MESSAGE(STATUS "BINARY dir is : " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "SOURCE dir is : " ${PROJECT_SOURCE_DIR})
MESSAGE(STATUS "output directory is : " ${CMAKE_BINARY_DIR})
MESSAGE(STATUS "qt select is : " ${QT_SELECT})

find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)

include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
add_definitions(-DTESTCASE)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")  
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set (kscope_FORMS
    ${PROJECT_SOURCE_DIR}/src/ui/makelayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/cscopemsglayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/prefcolorlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/preffontlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/prefoptlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/preffrontendlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/querywidgetlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/openprojectlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/queryviewlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/autocompletionlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/newprojectlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/searchresultslayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/scanprogresslayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/fileviewlayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/projectfileslayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/welcomedlg.ui
    ${PROJECT_SOURCE_DIR}/src/ui/symbollayout.ui
    ${PROJECT_SOURCE_DIR}/src/ui/bookmarkslayout.ui
    )

QT4_WRAP_UI(kscope_FORMS_HEADERS ${kscope_FORMS})

aux_source_directory(${PROJECT_SOURCE_DIR}/src kscope_SRCS)

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
