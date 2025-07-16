#include <stdio.h>
#include <netinet/in.h>
#include <nuttx/config.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

bool g_webmorda_started = false;

static int webmorda(int argc, FAR char *argv[])
{
    g_webmorda_started = true;

    struct addrinfo hints, *res;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int ret = getaddrinfo("google.com", "80", &hints, &res);
    if (ret != 0) {
        printf("Unable to resolve adress, quitting\n");
        return EXIT_FAILURE;
    }

    usleep(100 * 1000);

    while (true) {
        sleep(1);
    }

    return EXIT_SUCCESS;
}

extern "C" int main(int argc, FAR char *argv[])
{
    if (g_webmorda_started) {
        printf("webmorda_main: webmorda is already running\n");
        return EXIT_SUCCESS;
    }

    int ret = task_create(CONFIG_MODULES_WEBMORDA_PROGNAME,
                          CONFIG_MODULES_WEBMORDA_PRIORITY,
                          CONFIG_MODULES_WEBMORDA_STACKSIZE,
                          webmorda,
                          NULL);

    if (ret < 0) {
        int errcode = errno;
        printf("webmorda_main: Failed to start webmorda: %d.\n", errcode);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
