#include <nuttx/config.h>

#include <sched.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <nuttx/leds/userled.h>
#include <unistd.h>

bool g_heartbeat_started = false;

static int heartbeat_daemon(int argc, char *argv[])
{
    int ret;

    g_heartbeat_started = true;
    printf("heartbeat_daemon: Running.\n");

    char *fd_path = "/dev/userleds";
    int fd = open(fd_path, O_WRONLY);
    if (fd < 0) {
        int errcode = errno;
        printf("heartbeat_daemon: Failed to open %s:%d.\n", fd_path, errcode);
        close(fd);
        return EXIT_FAILURE;
    }

    struct userled_s heartbeat_led = {
        .ul_led = 0,
        .ul_on = false,
    };

    while (true) {
        heartbeat_led.ul_on = !heartbeat_led.ul_on;
        ret = ioctl(fd, ULEDIOC_SETLED, &heartbeat_led);
        if (ret < 0) {
            int errcode = errno;
            printf("heartbeat_daemon: Error with ioctl: %d.\n", errcode);
            close(fd);
            return EXIT_FAILURE;
        }

        usleep(500 * 1000);
    }

    return EXIT_SUCCESS;
}

int main(int argc, FAR char *argv[])
{
    printf("heartbeat_main: Starting heartbeat led daemon.\n");

    if (g_heartbeat_started) {
        printf("heartbeat_main: heartbeat led daemon is already running\n");
        return EXIT_SUCCESS;
    }

    int ret = task_create("heartbeat_daemon",
                           CONFIG_CUSTOM_APP_PRIORITY,
                           CONFIG_CUSTOM_APP_STACKSIZE,
                           heartbeat_daemon,
                           NULL);

    if (ret < 0) {
        int errcode = errno;
        printf("heartbeat_main: Failed to create heartbeat_daemon: %d.\n", errcode);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

