#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

void ssu_addone(void);

extern char **environ;
char glob_var[] = "HOBBY=swimming";

int main()
{
	struct timeval start, end;
	int i;

	gettimeofday(&start,NULL);
	for( i =0; environ[i] != NULL; i++)
		printf("environ[%d] : %s\n",i,environ[i]);  //환경을 출력합니다.
	putenv(glob_var);  //환경에 glob_var를 추가합니다.
	ssu_addone();  //환경에 LOVER를 추가합니다.
	printf("My hobby is %s\n",getenv("HOBBY"));
	printf("My lover is %s\n",getenv("LOVER"));
	strcpy(glob_var + 6,"fishing");

	for(i = 0; environ[i] != NULL; i++)
		printf("environ[%d] : %s\n",i,environ[i]);

	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}

void ssu_addone(void) {
	char auto_var[10];

	strcpy(auto_var,"LOVER=js");  //auto_var변수에 값을 저장합니다.
	putenv(auto_var);  //환경에 auto_var를 추가합니다.
}
