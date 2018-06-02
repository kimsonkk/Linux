#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
	struct stat statbuf;  //stat구조체를 저장하기 위한 변수입니다.
	char *fname = "ssu_myfile";
	int fd;

	if((fd = open(fname, O_RDWR | O_CREAT, 0600)) <0) {  //fname의 파일을 0600mode로 만들어 열고 실패 시 에러메세지를 출력하고 종료합니다.
		fprintf(stderr,"open error for %s\n",fname);
		exit(1);
	}

	close(fd);
	stat(fname,&statbuf);  //fname의 stat구조체를 가져옵니다.
	printf("# 1st call # UID:%d   GID:%d\n",statbuf.st_uid, statbuf.st_gid);
	if(chown(fname,501,300) < 0) {  //fname의 사용자 ID와 Group ID를 변경합니다.
		fprintf(stderr, "chown error for %s\n",fname);
		exit(1);
	}

	stat(fname,&statbuf);  //fname의 stat구조체를 가져옵니다.
	printf("# 2nd stat call # UID:%d   GID:%d\n",statbuf.st_uid, statbuf.st_gid);
	if (unlink(fname) <0) {  //fname의 링크들을 제거합니다.
		fprintf(stderr,"unlink error for %s\n",fname);
		exit(1);
	}
	exit(0);
}
