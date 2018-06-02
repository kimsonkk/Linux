#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

int main(int argc, char *argv[]) 
{
	struct ssu_employee record;
	int fd;
	int record_num;

	if(argc <2) {  //실행할 때 입력받은 인자가 없으면 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"Usage : %s file\n",argv[0]);
		exit(1);
	}

	if(( fd = open(argv[1], O_RDONLY)) < 0) {  //file명을 입력받아 그 파일을 읽기 모드로 열고 예외 처리를 합니다
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	while(1)
	{
		printf("Enter record number : ");
		scanf("%d", &record_num);

		if(record_num < 0) //입력 받은 수가 음수일 경우 반복문을 나갑니다
			break;

		if(lseek(fd, (long)record_num*sizeof(record), 0) <0 )   //입력받은 record_num만큼 파일의 file의 오프셋을 이동시킵니다
		{
			fprintf(stderr , "lseek error\n");
			exit(1);
		}

		if(read(fd,(char*)&record, sizeof(record)) > 0)  //file에서 record의 크기만큼 읽어 record에 저장합니다
			printf("Employee %s Salary : %d\n", record.name,record.salary);  //record의 정보를 출력합니다
		else
			printf("Record %d not found \n", record_num);
	}

	close(fd);
	exit(0);
}
