#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <sys/time.h>

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register);

static jmp_buf glob_buffer;  //stack 환경과 register환경을 저장할 변수입니다.

int main()
{
	struct timeval start,end;
	register int loc_register;  //register 변수를 선언합니다.
	volatile int loc_volatile;  //volatile 변수를 선언합니다.
	int loc_var;

	gettimeofday(&start,NULL);
	loc_var = 10;
	loc_volatile = 11;
	loc_register = 12;

	if(setjmp(glob_buffer) != 0) {  //iongjmp에서 setjmp함수를 호출했을 때 저장되는 변수를 출력합니다.
		printf("after longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n", 
				loc_var, loc_volatile, loc_register);
		exit(0);
	}

	loc_var = 80;
	loc_volatile = 81;
	loc_register = 83;
	ssu_nested_func(loc_var, loc_volatile, loc_register);
	gettimeofday(&end,NULL);
	printf("time : %f\n",end.tv_sec - start.tv_sec + end.tv_usec/1000000.0 - start.tv_usec/1000000.0);
	exit(0);
}

void ssu_nested_func(int loc_var, int loc_volatile, int loc_register) {
//인자로 받아온 변수들을 출력하고 longjmp를 호출하여 setjmp의 위치로 이동합니다.
	printf("before longjmp, loc_var = %d, loc_volatile = %d, loc_register = %d\n",
			loc_var, loc_volatile, loc_register);
	longjmp(glob_buffer,1);
}
