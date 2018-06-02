#ifndef SSU_MAKE
#define SSU_MAKE

//Command를 저장하기 위한 구조체
typedef struct __ComNode{
	char *Command;  //Command
	int cline;  //Command가 포함된 줄
	struct __ComNode *next;
}ComNode;

//Dependency를 저장하기 위한 구조체
typedef struct __DepNode{
	char *Dependency;  //Dependency
	struct __DepNode *next;
}DepNode;

//Target을 저장하기 위한 구조체
typedef struct __TargetNode{
	char *Target;  //Target
	DepNode* Dep;  //Target의 Dependency
	ComNode* Com;  //Target의 Command
	int line;  //Target이 포함된 줄
	struct __TargetNode *next;
}TargetNode;

//Macro를 저장하기 위한 구조체
typedef struct __MacroNode{
	char *Macro;  //Macro
	char *Value;  //Value
	int mline;  //Macro가 포함된 줄
	char state;  //Macro의 상태 변환 가능한지 불가능한 지를 저장
	struct __MacroNode *next;
}MacroNode;

//Target을 관리하기 위한 구조체
typedef struct __TargetList {
	TargetNode *head; //첫 Target
	TargetNode *cur;
}TargetList;

//Macro를 관리하기 위한 구조체
typedef struct __MacroList {
	MacroNode *head;  //첫 Macro
	MacroNode *cur;
}MacroList;

#endif
