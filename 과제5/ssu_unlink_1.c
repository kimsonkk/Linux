#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char* fname = "ssu_dump.txt";

	if(open(fname, O_RDWR) < 0) {  //fname을 혼용 모드로 열어온다.
		fprintf(stderr, "open error for %s\n",fname);  //실패 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	if(unlink(fname) < 0) {  //fname의 링크를 제거해준다.
		fprintf(stderr,"unlink error for %s\n",fname);  //실패 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	printf("file unlinked\n");
	sleep(20);
	printf("Done\n");
	exit(0);
}

