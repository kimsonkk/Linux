#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	struct stat file_info;  //읽어온 file의 구조체를 저장할 변수입니다.
	char* str;  //file의 종류를 저장할 변수입니다.
	int i;

	for(i = 1; i < argc; i++) {  //입력받은 파일의 개수만큼 반복합니다
		printf("name = %s, type = ", argv[i]);  //file의 이름과 타입을 출력합니다.

		if(lstat(argv[i], &file_info) < 0) {  //file의 구조체를 가져올 때 에러 시 예외 처리를 하고 종료합니다.
			fprintf(stderr, "lstat error\n");
			exit(1);
		}

		/*읽어온 file의 종류 및 모드를 읽어와서
		  그 file의 종류에 따라 str에 그 파일의
		  종류를 저장합니다.
		 */
		if(S_ISREG(file_info.st_mode))
			str = "regular";
		else if (S_ISDIR(file_info.st_mode))
			str = "directory";
		else if (S_ISCHR(file_info.st_mode))
			str = "character special";
		else if (S_ISBLK(file_info.st_mode))
			str = "block special";
		else if (S_ISFIFO(file_info.st_mode))
			str = "FIFO";
		else if (S_ISLNK(file_info.st_mode))
			str = "symbolic link";
		else if (S_ISSOCK(file_info.st_mode))
			str = "socket";
		else
			str = "unknown mode";

		printf("%s\n",str);  //file의 종류를 출력합니다.
	}
	exit(0);
}
