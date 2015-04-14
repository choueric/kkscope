project (husky_test)
find_package (KDE4 REQUIRED)
find_package (Qt4 REQUIRED)
include (KDE4Defaults)
include (${QT_USE_FILE})
include_directories (${KDE4_INCLUDES})
include_directories (${PROJECT_SOURCE_DIR}/../../)
add_definitions(-DTESTCASE)
set (husky_SRCS 
    main.cpp 
    mainwin.cpp
    ../../ctagslist.cpp
    ../../frontend.cpp
    ../../ctagsfrontend.cpp
    ../../kscopeconfig.cpp
    ../../searchlist.cpp)
kde4_add_executable (husky_test ${husky_SRCS})
target_link_libraries (husky_test ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${QT_LIBRARIES})
install(TARGETS husky_test ${INSTALL_TARGETS_DEFAULT_ARGS})
