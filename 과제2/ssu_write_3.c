#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

int main(int argc, char *argv[]) 
{
	struct ssu_employee record;
	int fd;

	if( argc < 2) {  //실행 파일 이외에 글자가 없을 경우 에러 메세지를 출력하고 종료한다
		fprintf(stderr,"usage : %s file\n",argv[0]);
		exit(1);
	}

	if (( fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0) {  //argv[1]의 이름으로 file을 쓰기 모드로 만들고 open할 떄 이미 같은 이름의 파일이 있다면 에러를 출력한다
		fprintf(stderr,"open error for %s\n",argv[1]);
		exit(1);
	}

	while(1) {
		printf("Enter employee name <SPACE> salary : ");
		scanf("%s", record.name);

		if(record.name[0] == '.')  //입력한 글자의 첫 글자가 .이면 종료한다
			break;

		scanf("%d",&record.salary);
		record.pid = getpid();
		write(fd,(char*)&record, sizeof(record))  //입력한 글자의 첫 글자가 .이면 종료한다;
	}

	close(fd);
	exit(0);
}
