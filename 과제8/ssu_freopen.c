#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *fname = "ssu_test.txt";
	int fd;

	printf("First printf : Hello, OSLAB!!\n");

	if((fd = open(fname, O_RDONLY)) < 0) {  //open이용해 fname의 파일을 읽기 모드로 열어옵니다.
		fprintf(stderr,"open error for %s\n",fname);
		exit(1);  //에러 시 예외처리를 합니다.
	}

	if(freopen(fname,"w",stdout) != NULL)  //fname의 파일로 표준 출력을 쓰기 권한으로 다시 열어옵니다.
		printf("Second printf : Hello, OSLAB!!\n");  //fname의 파일에 출력합니다.

	exit(0);
}
