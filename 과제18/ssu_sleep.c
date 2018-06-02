#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void ssu_timestamp(char *str);

int main(void)
{
	unsigned int ret;

	ssu_timestamp("before sleep()");
	ret = sleep(10);  //프로세스를 10초간 일시 정지 상태로 만듭니다.
	ssu_timestamp("after sleep()");
	printf("sleep() returned %d\n", ret);
	exit(0);
}

void ssu_timestamp(char *str) {
	time_t time_val;

	time(&time_val);  //현재시간을 가져옵니다.
	printf("%s the time is %s\n", str, ctime(&time_val));  //현재 시간을 출력합니다.
}
