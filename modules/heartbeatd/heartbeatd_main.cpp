#include <nuttx/config.h>
#include <sched.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <nuttx/leds/userled.h>

bool g_heartbeat_started = false;

static int heartbeatd(int argc, char *argv[])
{
    int ret;

    g_heartbeat_started = true;

    const char *fd_path = "/dev/userleds";
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
            printf("heartbeatd: Error with ioctl: %d.\n", errcode);
            close(fd);
            return EXIT_FAILURE;
        }

        usleep(500 * 1000);
    }

    return EXIT_SUCCESS;
}

extern "C" int main(int argc, FAR char *argv[])
{
    if (g_heartbeat_started) {
        printf("heartbeatd_main: heartbeatd is already running\n");
        return EXIT_SUCCESS;
    }

    int ret = task_create(CONFIG_MODULES_HEARTBEATD_PROGNAME,
                          CONFIG_MODULES_HEARTBEATD_PRIORITY,
                          CONFIG_MODULES_HEARTBEATD_STACKSIZE,
                          heartbeatd,
                          NULL);

    if (ret < 0) {
        printf("heartbeatd_main: Failed to start heartbeatd: %d.\n", errno);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
