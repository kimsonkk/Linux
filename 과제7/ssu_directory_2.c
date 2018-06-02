#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define MAX_PATH_GUESSED 1024

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

char *pathname;  //경로를 저장하는 변수입니다.
char command[LINE_MAX], grep_cmd[LINE_MAX];  //명령어와 grep한 줄의 내용을 저장할 변수입니다.

int ssu_do_grep() {  //
	struct dirent *dirp;
	struct stat statbuf;
	char *ptr;
	DIR *dp;

	if(lstat(pathname,&statbuf) < 0) {  //pathname의 stat구조체 정보를 가져옵니다.
		fprintf(stderr, "lstat  error for %s\n",pathname);  //실패할 경우 에러 메세지를 출력합니다.
		return 0;
	}

	if(S_ISDIR(statbuf.st_mode) == 0) {  /*pathname이 디렉터리가 아닐 경우
										   systme함수를 이용해서 pathname의
										   내용을 grep합니다.*/
		sprintf(command,"%s %s",grep_cmd,pathname);
		printf("%s : \n",pathname);
		system(command);
		return 0;
	}

	ptr = pathname + strlen(pathname);
	*ptr++ = '/';
	*ptr = '\0';  //pathname의 뒤에 /을 추가합니다.

	if((dp = opendir(pathname)) == NULL) {  //pathname의 DIR구조체를 가져와 dp에 저장합니다.
		fprintf(stderr,"opendir error for %s\n",pathname);  //실패할 경우 에러 메세지를 출력하고 종료합니다.
		return 0;
	}
	while((dirp = readdir(dp)) != NULL)  //dirent가 NULL일 때까지 반복합니다.
		if(strcmp(dirp->d_name,".") &&strcmp(dirp->d_name, "..")) {  //. 이나 ..일 경우 ptr에 복사합니다.
			strcpy(ptr,dirp->d_name);

			if(ssu_do_grep() <0)
				break;
		}
	ptr[-1] = 0;
	closedir(dp);
	return 0;
}

void ssu_make_grep(int argc, char *argv[]) {  //grep을 하기 위해 문장을 읽어와 grep_cmd에 복사합니다.
	int i;
	strcpy(grep_cmd," grep");
	for(i =1; i< argc -1; i++) {
		strcat(grep_cmd," ");
		strcat(grep_cmd,argv[i]);
	}
}

int main(int argc, char *argv[]) 
{
	struct timeval start,end;
	double op_time;

	gettimeofday(&start,NULL);
	if( argc < 2) {  //인자가 2개 미만일 경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"usage : %s <-CVbchilnsvwx> <-num> <-A num> <-B num> <-f file> \n" "       <-e> expr <directory>\n",argv[0]);
		exit(1);
	}

	if(pathmax == 0) {  //경로가 없을 경우 //경로를 잡아줍니다.
		if((pathmax = pathconf("/",_PC_PATH_MAX)) < 0)
			pathmax = MAX_PATH_GUESSED;
		else
			pathmax++;
	}

	if((pathname = (char*)malloc(pathmax+1)) == NULL) {  //pathname이 NULL일 경우 에러 메세지를 출력하고 종료합니다.
		fprintf(stderr,"malloc error\n");
		exit(1);
	}

	strcpy(pathname,argv[argc-1]);  //목정 경로를 복사합니다.
	ssu_make_grep(argc,argv);  //grep_cmd를 저장합니다.
	ssu_do_grep();
	
	gettimeofday(&end,NULL);
	op_time = end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0;
	printf("time : %f\n",op_time);
	exit(0);
}
