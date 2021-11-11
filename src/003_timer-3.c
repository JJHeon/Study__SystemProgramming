/**
 * TestCode For CLI-Tetris
 * Alarm  timer_create, timer_settime ~
 */
#define _POSIX_C_SOURCE 199309L
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
/**
 * si : 시그널이 발생한 원인을 담은 siginfo_t 구조체 포인터
 * ucontext : 시그널이 전달될 때 시그널을 받는 프로세스의 내부 상태를 나타내는 ucontext_t 구조체포인터
 */
void sigaction_handler(int signo, siginfo_t* si, void* ucontext) {
    // Try 1
    // printf("signo : %d, si_signo : %d, value : %d\n", signo, si->si_signo, si->_sifields._rt.si_sigval.sival_int); // NUM 14면 SIGALRM
    // Try 2
    printf("signo : %d, si_signo : %d, timer 3 : %#jx\n", signo, si->si_signo, *(timer_t*)si->_sifields._rt.si_sigval.sival_ptr);  // NUM 14면 SIGALRM
}

int main() {
    timer_t timer;
    int ret = 0;
    printf("declear1 | timer ID is %#jx\n", (uintmax_t)timer);
    // Signal Set
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGALRM);

    struct sigaction sigac = {
        .sa_flags = SA_SIGINFO,
        .sa_sigaction = sigaction_handler,
        .sa_mask = set};

    sigaction(SIGALRM, &sigac, NULL);

    struct sigevent evp;
    // Try 1
    // evp.sigev_value.sival_int = 500;  //임의 지정
    evp.sigev_value.sival_ptr = &timer;
    evp.sigev_notify = SIGEV_SIGNAL;
    evp.sigev_signo = SIGALRM;
    ret = timer_create(CLOCK_REALTIME, &evp, &timer);  // evp가 NULL이면 SIGARM , Value는 Timer id
    if (ret) perror("timer_create");

    printf("another type | timer ID is %#jx\n", (uintmax_t)timer);

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

    timer_delete(timer);
    printf("end | timer ID is %#jx\n", (uintmax_t)timer);

    return 0;
}