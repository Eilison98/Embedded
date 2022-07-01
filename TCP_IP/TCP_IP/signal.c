#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// 시그널이 발생했을 때 호출되어야 할 함수가 각각 정의되어 있다.
// 이러한 유형의 함수를 가리켜 시그널 핸들러라 한다.
void timeout(int sig)
{
	if(sig == SIGALRM)
		puts("Time out!");

	// 2초 간격으로 SIGALRM 시그널을 반복 발생시키기 위해
	// 시그널 핸들러 내에서 alarm함수를 호출하고 있다.
	alarm(2);
}

// 시그널이 발생했을 때 호출되어야 할 함수가 각각 정의되어 있다.
// 이러한 유형의 함수를 가리켜 시그널 핸들러라 한다.
void keycontrol(int sig)
{
	if(sig == SIGINT)
		puts("CTRL+C pressd");
}

int main(int argc, char *argv[])
{
	int i;
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);
	alarm(2);

	for(i=0; i<3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	return 0;
}
