if(CONFIG_MODULES_WEBMORDA)
    set(SOURCES
        webmorda_main.cpp
    )

    nuttx_add_application(
        NAME
        ${CONFIG_MODULES_WEBMORDA_PROGNAME}
        PRIORITY
        ${CONFIG_MODULES_WEBMORDA_PRIORITY}
        STACKSIZE
        ${CONFIG_MODULES_WEBMORDA_STACKSIZE}
        MODULE
        ${CONFIG_MODULES_WEBMORDA}
        SRCS
        ${SOURCES})

    nuttx_add_cromfs(
        NAME
        web-interface
        PATH
        ${CMAKE_CURRENT_SOURCE_DIR}/web-interface)

    target_link_libraries(apps PRIVATE cromfs_web-interface)
endif()
