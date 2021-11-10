/**
 * clock 해상도 Test
 * 코드의 문제가 있음 time.h 에 CLOCK_ 관련 매크로가 있어야하지만.. 시간이 지나서 변했는지?
 * CLI-Tetris project 위한 테스트
 */
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
    __clockid_t clocks[] = {
        CLOCK_REALTIME,
        CLOCK_MONOTONIC,
        CLOCK_PROCESS_CPUTIME_ID,
        CLOCK_THREAD_CPUTIME_ID,
        CLOCK_MONOTONIC_RAW,
        (__clockid_t)-1};
    int i;

    for (i = 0; clocks[i] != (__clockid_t)-1; i++) {
        struct timespec res;
        int ret;

        ret = clock_getres(clocks[i], &res);
        if (ret)
            perror("clock_getres");
        else
            printf("clock=%d sec=%ld nsec=%ld\n", clocks[i], res.tv_sec, res.tv_nsec);
    }

    return 0;
}