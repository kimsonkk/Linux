#include <stdio.h>
#include <stdlib.h>

void ssu_printenv(char *label, char ***envpp);

extern char **environ;

int main(int argc, char *argv[], char *envp[])
{
	ssu_printenv("Initially", &envp);  //Initially와 환경변수를 인자로 함수를 호출합니다.
	putenv("TZ=PSTSPDT");  //환경 변수를 추가합니다.
	ssu_printenv("After changing TZ", &envp);  //환경 변수를 출력합니다.
	putenv("WARNING=Don't use envp after putenv()");  //환경 변수를 추가합니다.
	ssu_printenv("After setting a new variable", &envp);  //환경 변수들을 출력합니다.
	printf("value of WARNING is %s\n",getenv("WARNING"));
	exit(0);
}

void ssu_printenv(char *label, char ***envpp) {
	//환경 변수들을 전부 출력합니다.
	char **ptr;

	printf("---- %s ---\n",label);
	printf("envp is at %8o and contains %8o\n",envpp, &envpp);
	printf("environ is at %8o and contains %8o\n", &environ, environ);
	printf("My environment variable are:\n");

	for(ptr = environ; *ptr ; ptr++)  //환경변수들을 출력합니다.
		printf("(%8o) = %8o -> %s\n", ptr, *ptr, *ptr);
	printf("(%8o) = %8o\n",ptr, *ptr);
}
