if(CONFIG_MODULES_HEARTBEATD)
    nuttx_add_application(
        NAME
        ${CONFIG_MODULES_HEARTBEATD_PROGNAME}
        PRIORITY
        ${CONFIG_MODULES_HEARTBEATD_PRIORITY}
        STACKSIZE
        ${CONFIG_MODULES_HEARTBEATD_STACKSIZE}
        MODULE
        ${CONFIG_MODULES_HEARTBEATD}
        SRCS
        heartbeatd_main.cpp)
endif()
