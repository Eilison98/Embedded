#include <stdio.h>
#include <unistd.h>

int gval = 10;

int main(int argc, char *argv[])
{
	pid_t pid;
	int lval = 20;
	gval++, lval+=5;

	// fork();
	// 자식 프로세스를 생성하고있다.
	// 따라서 부모 프로세스의 pid에는 자식프로세스의 ID가 저장되며,
	// 자식 프로세스의 pid에는 0이 저장된다.
	pid = fork();

	// 자식 프로세스가 실행 pid에 0이 저장되기 때문이다.
	if(pid == 0)
		gval+=2, lval+=2;
	else
		// 부모 프로세스가 실행 pid에 자식 프로세스의 ID가 저장되기 떄문이다.
		gval-=2, lval-=2;

	if(pid == 0)
		// 자식 프로세스가 실행 pid에 0이 저장되기 때문이다.
		printf("Child Proc: [%d, %d] \n", gval, lval);
	else
		// 부모 프로세스가 실행 pid에 자식 프로세스의 ID가 저장되기 떄문이다.
		printf("Parent Proc: [%d, %d] \n", gval, lval);
	return 0;
}
