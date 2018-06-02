#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *argv[] = {
		"ssu_execl_test_1","param1","param2",(char *)0
	};

	printf("this is the original program\n");
	execv("./ssu_execl_test_1",argv);  //execv함수를 이용해서 새로운 프로그램을 만들어 실행합니다.
	printf("%s\n", "This line should never get printed\n");
	exit(0);
}
