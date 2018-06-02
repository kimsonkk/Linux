#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage : a.out pathname");
		exit(1);
	}
	if(access(argv[1] , R_OK) < 0)
		printf("access error for %s\n",argv[1]);
	else 
		printf("Read access PK\n");
	if(open(argv[1],O_RDONLY) < 0)
		printf("opem rrror for %s\n",argv[1]);
	else 
		printf("open for reading OK\n");
	exit(0);
}
