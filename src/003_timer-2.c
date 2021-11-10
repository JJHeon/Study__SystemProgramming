/**
 * TestCode For CLI-Tetris
 * Alarm  timer_create, timer_settime ~
 */
#define _POSIX_C_SOURCE 199309L
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>

void alarm_handler(int value) {
    printf("Call SIG Handler NUM : %d\n", value);  // NUM 14면 SIGALRM
}
void alarm_handler_user(int value) {
    printf("Call SIG Handler Users NUM : %d\n", value);  // NUM 14면 SIGALRM
}

int main() {
    timer_t timer;
    int ret = 0;

    // Signal Set
    signal(SIGALRM, alarm_handler);
    signal(SIGUSR1, alarm_handler_user);

    // Create Timer //CLOCK_PROCESS_CPUTIME_ID 하니까 안됨
    /*
    //Try one
    ret = timer_create(CLOCK_REALTIME, NULL, &timer);  // evp가 NULL이면 SIGARM , Value는 Timer id
    if (ret) perror("timer_create");
    */
    // Try second
    struct sigevent evp;
    evp.sigev_value.sival_ptr = &timer;
    evp.sigev_notify = SIGEV_SIGNAL;
    evp.sigev_signo = SIGUSR1;
    ret = timer_create(CLOCK_REALTIME, &evp, &timer);  // evp가 NULL이면 SIGARM , Value는 Timer id
    if (ret) perror("timer_create");

    printf("timer id : %d\n", *(int*)timer);
    //이렇게 사용하는 것이 아님, sigev_value는 sigaction과 함께 사용되어야함
    // printf("evp sigev_value int: %d\n", evp.sigev_value.sival_int);
    // printf("evp sigev_value point: %d\n", *(int*)evp.sigev_value.sival_ptr);

    // Timer Start
    struct itimerspec ts;
    int ret2;
    ts.it_interval.tv_sec = 0;
    ts.it_interval.tv_nsec = 0;
    ts.it_value.tv_sec = 5;
    ts.it_value.tv_nsec = 0;
    ret2 = timer_settime(timer, 0, &ts, NULL);
    if (ret) perror("timer_settime");

    // Sleep
    struct timespec t = {.tv_sec = 15, .tv_nsec = 200};
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
    //이렇게 사용하는 것이 아님, sigev_value는 sigaction과 함께 사용되어야함
    // printf("evp sigev_value : %d\n", evp.sigev_value.sival_int);
    // printf("evp sigev_value point: %d\n", *(int*)evp.sigev_value.sival_ptr);

    return 0;
}