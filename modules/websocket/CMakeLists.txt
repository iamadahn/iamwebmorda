if(CONFIG_MODULES_WEBSOCKET)
    nuttx_add_application(
        NAME
        ${CONFIG_MODULES_WEBSOCKET_PROGNAME}
        PRIORITY
        ${CONFIG_MODULES_WEBSOCKET_PRIORITY}
        STACKSIZE
        ${CONFIG_MODULES_WEBSOCKET_STACKSIZE}
        MODULE
        ${CONFIG_MODULES_WEBSOCKET}
        SRCS
        websocket_main.cpp)

    set(INCDIRS
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/cxx
        ${CMAKE_BINARY_DIR}/include
    )

    add_subdirectory(wsServer)
    target_include_directories(ws PUBLIC ${INCDIRS})
    target_link_libraries(apps_websocket ws)
endif()
