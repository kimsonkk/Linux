#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

struct stat statbuf;  //stat 구조체를 저장할 변수입니다.

void ssu_checkfile(char* fname, time_t *time);  //file의 정보를 읽어 파일의 변경 여부를 확인하는 함수입니다.

int main(int argc, char* argv[])
{
	time_t intertime;  //file의 마지막 수정된 시간을 저장할 변수입니다.

	if(argc != 2) {  //인자로 받은 명령어의 개수가 2개가 아니면 예외처리를 하고 종료합니다.
		fprintf(stderr,"usage : %s <file>\n", argv[0]);
		exit(1);
	}

	if(stat(argv[1], &statbuf) < 0) {  //입력받은 file의 stat구조체를 가져올 때 에러 시 예외처리를 하고 종료합니다.
		fprintf(stderr, "stat error for %s\n", argv[1]);
		exit(1);
	}

	intertime = statbuf.st_mtime;  //가져온 stat구조체에서 마지막 수정된 시간을 저장합니다.
	while(1) {
		ssu_checkfile(argv[1], &intertime);  //가져온 file의 시간을 비교합니다.
		sleep(10);  //10ms동안 프로그램을 지연시킵니다.
	}
}

void ssu_checkfile(char* fname, time_t *time) {
	if (stat(fname, &statbuf) < 0) {  //fname의 file의 stat구조체를 가져올 때 에러시 예외처리를 하고 종료합니다.
		fprintf(stderr, "Warning : ssu_checkfile() error!\n");
		exit(1);
	}
	else
		if (statbuf.st_mtime != *time) {  /*가져온 stat구조체의 마지막 수정 시간과 처음 가져온 시간과 일치하지 않을
											경우 경고 메세지를 출력하고 마지막 수정시간을 저장합니다*/
			printf("Warning : %s was modified!.\n",fname);
			*time = statbuf.st_mtime;
		}
}
