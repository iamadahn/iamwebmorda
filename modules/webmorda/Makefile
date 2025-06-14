include $(APPDIR)/Make.defs

PROGNAME = $(CONFIG_MODULES_WEBMORDA_PROGNAME)
PRIORITY = $(CONFIG_MODULES_WEBMORDA_PRIORITY)
STACKSIZE = $(CONFIG_MODULES_WEBMORDA_STACKSIZE)
MODULE = $(CONFIG_MODULES_WEBMORDA)

CXXEXT = .cpp
MAINSRC = webmorda_main.cpp

MAINSRC += networking/server.cpp
MAINSRC += networking/sockets/simple_socket.cpp
MAINSRC += networking/sockets/listening_socket.cpp
MAINSRC += networking/sockets/binding_socket.cpp
MAINSRC += networking/sockets/connecting_socket.cpp

include $(APPDIR)/Application.mk
