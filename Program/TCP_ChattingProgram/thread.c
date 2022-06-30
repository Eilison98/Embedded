//  표준 라이브러리 함수
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <pthread.h>

int a = 0;
pthread_mutex_t mutex;

void * thread1(void * arg)
{
	//  보이드 포인터를 인트형식으로 프린트한다.
	printf("arg : %d\n", (int)arg);

	while(1)
	{
		printf("thread%d : a[%d]\n",(int)arg, a++);
		sleep(2);
	}
	return NULL;
}

int main()
{
	//  window의 핸들 같은거
	pthread_t s_thread[2];

	//  유저 아이디 
	int id1 = 77;
	int id2 = 88;

	//  NULL = Fast
	pthread_mutex_init(&mutex, NULL);

	//  쓰레드 생성
	pthread_create(&s_thread[0], NULL, thread1, (void *)id1);
	pthread_create(&s_thread[1], NULL, thread1, (void *)id2);

	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf(" Main Loop \n");
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	//  쓰레드 조인
	//  쓰레드가 끝날때 까지 기다려주는 그런
	//  pthread_join(s_thread[0], NULL);
	//  pthread_join(s_thread[1], NULL);
}
