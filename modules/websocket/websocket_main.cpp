#include <nuttx/config.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "wsServer/include/ws.h"
#include "pthread.h"

bool g_websocket_started = false;

void onopen(ws_cli_conn_t client)
{
    char *cli, *port;
    cli = ws_getaddress(client);
    port = ws_getport(client);
    printf("websocket: Connection opened, addr: %s, port: %s.\n", cli, port);
}

void onclose(ws_cli_conn_t client)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("websocket: Connection closed, addr: %s.\n", cli);
}

void onmessage(ws_cli_conn_t client, const unsigned char *msg, uint64_t size, int type)
{
    char *cli;
    cli = ws_getaddress(client);
    printf("websocket: Received a message: %s (size: %" PRId64 ", type: %d), from: %s.\n",
           msg, size, type, cli);
    ws_sendframe_bcast(8080, (char *)msg, size, type);
}

static int websocket(int argc, char *argv[])
{
    struct ws_events events = {
        .onopen = &onopen,
        .onclose = &onclose,
        .onmessage = &onmessage,
    };

    struct ws_server server = {
        .host = "192.168.31.69",
        .port = 8080,
        .thread_loop = 0,
        .timeout_ms = 1000,
        .evs = events,
    };

    while (true) {
        ws_socket(&server);
    }

    pthread_mutex_lock(NULL);
}

extern "C" int main(int argc, FAR char *argv[])
{
    if (g_websocket_started) {
        printf("websocket_main: websocket is already running\n");
        return EXIT_SUCCESS;
    }

    int ret = task_create(CONFIG_MODULES_WEBSOCKET_PROGNAME,
                          CONFIG_MODULES_WEBSOCKET_PRIORITY,
                          CONFIG_MODULES_WEBSOCKET_STACKSIZE,
                          websocket,
                          NULL);

    if (ret < 0) {
        printf("websocket_main: Failed to start websocket: %d.\n", errno);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
