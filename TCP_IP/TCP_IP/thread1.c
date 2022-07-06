#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
void* thread_main(void *arg);

int main(int argc, char *argv[])
{
        pthread_t t_id;
        int thread_param = 5;

	// thread_main 함수의 호출을 시작으로 별도의 실행흐름을 구성하는 쓰레드의 생성을 요청하고 있다.
	// 더불어 thread_main  함수호출 시 인자로 변수 thread_param 의 주소 값을 전달하고 있다.
        if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_param)!=0)
	{
		puts("Pthread_Create() error");
		return -1;
	};

	// sleep 함수의 호출을 통해서 main함수의 실행을 10초간 중지시킨다.
	// 이는 프로세스의 종료시기를 늦추기 위함이다.
	sleep(10); puts("End of Main");
	return 0;
}

//  매개변수 arg로 전달되는 것은 10행에서 호출한 pthread_create 함수의 네 번째 전달인자이다.
void* thread_main(void *arg)
{
	int i;
	int cnt = *((int*)arg);
	for(i=0; i<cnt; i++)
	{
		sleep(1); puts("Running Thread");
	}
	return NULL;
}
