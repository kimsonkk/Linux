#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	char buf[64];
	char* fname = "ssu_tempfile";
	int fd;
	int length;

	if(( fd = open(fname,O_RDWR | O_CREAT | O_TRUNC,0600)) < 0 )  //fname의 이름으로 0600모드의 파일을 만들고 열어 옵니다.
	{
		fprintf(stderr,"first open error for %s\n",fname);  //실패 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	if(unlink(fname) < 0 ) {  //fname의 링크를 제거해 줍니다.
		fprintf(stderr,"unlink error for %s\n", fname);   //실패 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}

	if(write(fd, "How are you?", 12) != 12) {  //fd가 가리키는 파일에 글자를 입력합니다.
		fprintf(stderr, "write error\n");
		exit(1);
	}
	lseek(fd,0,0);

	if(( length = read(fd, buf, sizeof(buf))) < 0) {  //fd에서 buf의 사이즈 만큼 읽어 buf에 저장합니다.
		fprintf(stderr,"buf read error\n");  //실패 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	else
		buf[length] = 0;
	printf("%s\n",buf);
	close(fd);
	if((fd = open(fname, O_RDWR)) < 0) {  //fname을 혼용 모드로 읽어 옵니다.
		fprintf(stderr, "second open error for %s\n",fname);  //실패 시 에러 메세지를 출력하고 종료합니다.
		exit(1);
	}
	else
		close(fd);
	exit(0);
}
