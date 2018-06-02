#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TABLE_SIZE 128
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	static struct {  
		long offset;
		int length;
	} table [TABLE_SIZE];  //읽어온 file의 정보를 저장하는 구조체입니다

	char buf[BUFFER_SIZE];
	long offset;
	int entry;
	int i;
	int length;
	int fd;

	if(argc < 2) {  //명령행 옵션의 개수가 2개 이하이면 에러 메세지를 출력하고 종료합니다
		fprintf(stderr,"Usage: %s <file>\n",argv[0]);
		exit(1);
	}

	if (( fd = open(argv[1],O_RDONLY)) < 0) {  //argv[1]에 해당하는 file이 없으면 에러 메세지를 출력하고 종료합니다
		fprintf(stderr,"open error for %s\n", argv[1]);
		exit(1);
	}

	entry = 0;  //구조체 배열의 인덱스를 저장하기 위한 변수이다
	offset = 0;  //구조체의 offset을 저장하기 위한 변수이다
	
	while(( length = read(fd, buf,BUFFER_SIZE)) >0 ) {  
		for( i = 0; i < length; i++) {
			table[entry].length++;  //읽은 파일의 한 줄의 길이를 저장합니다
			offset++;  

			if(buf[i] == '\n')
				table[++entry].offset = offset;  //개행문자를 만나면 다음 구조체에 시작 offset을 저장합니다
		}
	}

#ifdef DEBUG  //DEBUG가 정의되어 있다면 #ifdef와 #endif 사이의 코드들을 컴파일합니다.
	for( i = 0; i < entry; i++) 
		printf("%d : %ld, %d\n",i + 1, table[i].offset, table[i].length);
#endif

	while(1) {
		printf("Enter line name : ");  //조회할 line을 입력받습니다.
		scanf("%d", &length);

		if(--length<0)  //1보다 작은 값을 입력할 경우 프로그램을 종료합니다
			break;

		lseek(fd, table[length].offset,0);  //파일의 읽어들일 지점의 offset을 이동시킵니다

		if(read(fd,buf,table[length].length) <= 0)  
			continue;

		buf[table[length].length] = '\0';  //buf의 한 줄의 마지막에 개행문자를 입력합니다
		printf("%s",buf);
	}

	close(fd);
	exit(0);
}
