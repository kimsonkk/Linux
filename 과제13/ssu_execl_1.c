#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("this is the original program\n");
	execl("./ssu_execl_test_1","ssu_execl_test_1",  //execl함수를 이용해서 새로운 프로그램을 만들어 실행합니다.
			"param1", "param2", "param3", (char *)0);
	printf("%s\n", "this line should never get printed\n");
	exit(0);
}
