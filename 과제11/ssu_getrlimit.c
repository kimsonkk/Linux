#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

#define ssu_show(limit) ssu_show_limit(limit,#limit)

void ssu_show_limit(int rlim_type, char *rlim_name);

int main()
{
	struct timeval start,end;
	gettimeofday(&start,NULL);
	printf("     resource soft limit hard limit    \n\n");
	ssu_show(RLIMIT_CPU); //프로세스가 소비할 수 있는 최대 CPU시간을 출력합니다.
	ssu_show(RLIMIT_FSIZE);  //파일 생성 시 파일의 최대 크기를 출력합니다.
	ssu_show(RLIMIT_DATA);  //자료 구역 전체의 최대 크기를 출력합니다.
	ssu_show(RLIMIT_STACK);  //스택의 최대 크기를 출력합니다.
	ssu_show(RLIMIT_CORE);  //한 코어 파일의 최대 크기를 출력합니다.
#ifdef RLIMIT_RSS
	ssu_show(RLIMIT_RSS);  //메모리 상주 세트 크기의 최대값을 출력합니다.
#endif
#ifdef RLIMIT_MEMLOCK
	ssu_show(RLIMIT_MEMLOCK);  //한 프로세스가 mlock으로 잠글수 있는 메모리의 최대 용량을 출력합니다.
#endif
#ifdef RLIMIT_NPORC
	ssu_show(RLIMIT_NPORC);  //실제 사용자의 ID당 최대 자식 프로세스 개수를 출력합니다.
#endif
#ifdef RLIMIT_OFILE
	ssu_show(RLIMIT_OFILE);  //한 프로세스가 열어둘 수 있는 최대 파일 개수를 출력합니다.
#endif
#ifdef RLIMIT_NOFILE
	ssu_show(RLIMIT_NOFILE);  //한 프로세스가 열어둘 수 있는 최대 파일 개수를 출력합니다.
#endif
#ifdef RLIMIT_VMEN
	ssu_show(RLIMIT_VEMN);  //한 프로세스의 총 가용 메모리의 용량의 최대값을 출력합니다.
#endif
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/100000.0 - start.tv_usec/1000000.0);

	exit(0);
}

void ssu_show_limit(int rlim_type, char *rlim_name) {
	//인자로 받아온 자원의 한계값을 출력하는 함수이다.
	struct rlimit rlim;
	char cur[11], max[11];

	getrlimit(rlim_type,&rlim);  //rlim_type의 자원의 한계 값을 조회하여 저장합니다.

	if(rlim.rlim_cur == RLIM_INFINITY)  //자원의 약한 한계 값이 무한대이면 cur에 infinity를 저장합니다.
		strcpy(cur,"infinity");
	else
		sprintf(cur, "%10ld", rlim.rlim_cur);  //무한대가 아니면 현재의 약한 한계를 저장합니다.

	if(rlim.rlim_max == RLIM_INFINITY)  //자원의 강한 한계 값이 무한대이면 max에 infinity를 저장합니다.
		strcpy(max, "infinity");
	else
		sprintf(max, "%10ld", rlim.rlim_max);  //무한대가 아니면 현재의 강한 한계를 저장합니다.

	printf("%15s : %10s %10s\n", rlim_name, cur, max);
}
