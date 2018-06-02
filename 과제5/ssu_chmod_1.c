#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
	struct stat statbuf;  //stat구조체를 저장할 변수입니다.
	char *fname1 = "ssu_file1";
	char *fname2 = "ssu_file2";

	if(stat(fname1, &statbuf) <0)  //fname1의 stat구조체를 받아오고 에러시 메세지를 출력합니다.
		fprintf(stderr,"stat error %s\n", fname1);
	if(chmod(fname1, (statbuf.st_mode & ~S_IXGRP) | S_ISUID) < 0)  //파일의 현재 모드에 Group의 실행권한을 빼고Usr의 실행권환을 추가하여 변경합니다.
		fprintf(stderr, "chmod srror %s\n", fname1);
	if(chmod(fname2, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH) < 0)  //파일의 모드를 0645로 변환합니다.
		fprintf(stderr,"chmod error %s\n",fname2);

	exit(0);
}
