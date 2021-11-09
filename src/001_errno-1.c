/**
 * errno 사용법
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(void) {
    /* ----------------------------------------------------------------------------------------------------------------------*/
    char* error_ptr = NULL;
    char error_buf[1024];

    errno = 0;
    int fd = open("error.txt", O_RDONLY);

    // errno는 함수호출 fail 이후에 사용되어야 한다.
    // errno는 자동으로 0으로 초기화되지 않는다.
    if (fd == -1) {
        //출력 결과 : 2, 이 값은 ENOENT 와 같다.
        printf("print errno 1: %d\n", errno);
        //실패한 함수 이름을 써주면 좋음
        //명시한 내용 뒤 colon(:) 을 붙이고 errno가 기술하는 현재 에러를 문자열로 바꾸어 stderr 출력
        perror("How to use perror? ");

        // string.h header, Not thread safe
        error_ptr = strerror(errno);
        printf("guide of using strerror : %s\n", error_ptr);

        // string.h header, thread safe
        strerror_r(errno, error_buf, sizeof(error_buf));
        printf("strerror_r : %s\n", error_buf);
    }

    // 22 line의 errno value와 비교했을때, 여전히 결과는 2이다.
    // errno는 자동으로 초기화되지 않는다.
    // 오류가 발생한 경우에만 재조정된다.
    // 만약 함수호출의 반환 타입의 전체 범위가 유효한 경우에는 errno를 먼저 0으로 초기화 한 후, 함수 호출해 errno를 검사한다.
    printf("print errno 2: %d\n", errno);

    errno = 0;

    /* ----------------------------------------------------------------------------------------------------------------------*/

    return 0;
}
