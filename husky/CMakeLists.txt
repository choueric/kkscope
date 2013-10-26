project (husky)
find_package (KDE4 REQUIRED)
include (KDE4Defaults)
include_directories (${KDE4_INCLUDES})
set (husky_SRCS 
    main.cpp 
    kscope.cpp 
    kscopeconfig.cpp 
    projectbase.cpp)
kde4_add_executable (husky ${husky_SRCS})
target_link_libraries (husky ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})
install(TARGETS husky ${INSTALL_TARGETS_DEFAULT_ARGS})
