/**
 * TestCode For CLI-Tetris
 * Alarm 및 nanosleep 기초 사용법
 */
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void alarm_handler(int signum) {
    printf("Five seconds passed!\n");
}

int main() {
    int ret = 0;
    signal(SIGALRM, alarm_handler);

    alarm(5);
    // sleep(15); //sleep이 SIGALRM을 사용한다.
    struct timespec t = {.tv_sec = 30, .tv_nsec = 200};
    struct timespec t2;
retry:
    ret = nanosleep(&t, &t2);  // nanosleep 은 signal에 영향을 받아 중간에 중단된다.
    if (ret == -1) {
        if (errno == EINTR) {
            t.tv_sec = t2.tv_sec;
            t.tv_nsec = t2.tv_nsec;
            goto retry;
        }
    }

    printf("End ret : %d\n", ret);
    return 0;
}