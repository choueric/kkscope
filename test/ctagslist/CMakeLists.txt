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

set (husky_SRCS 
    main.cpp 
    mainwin.cpp
    ../../src/ctagslistwidget.cpp
    ../../src/frontend.cpp
    ../../src/ctagsfrontend.cpp
    ../../src/stringlistmodel.cpp
    ../../src/kscopeconfig.cpp
    ../../src/kscopepixmaps.cpp
    ../../src/searchlistview.cpp)
kde4_add_executable (husky_test ${husky_SRCS})
target_link_libraries (husky_test ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS} ${QT_LIBRARIES})
install(TARGETS husky_test ${INSTALL_TARGETS_DEFAULT_ARGS})
