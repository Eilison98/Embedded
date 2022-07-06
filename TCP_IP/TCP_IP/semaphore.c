#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char * argv[])
{
	pthread_t id_t1, id_t2;

	// 세마포어를 두 개 생성하고 있다.
	// 하나의 세마포어 값은 0이고, 다른 하나는 1이다.
	sem_init(&sem_one, 0, 0);  // 1번 세마는 키가 없다.
	sem_init(&sem_two, 0, 1);  // 2는 세마는 키가 있다.

	// 스레드 생성
	pthread_create(&id_t1, NULL, read, NULL);
	pthread_create(&id_t2, NULL, accu, NULL);

	// 스레드 조인(대기)
	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	// 세마포어 객체를 삭제하고 할당된 자원을 해제
	sem_destroy(&sem_one);
	sem_destroy(&sem_two);
	return 0;
}

// 입력
void * read(void * arg)
{
	int i;
	for(i=0; i<5; i++)
	{
		fputs("Input num: ", stdout);

		// 키를 획득하는 함수, 획득하면 1감소
		// 세마포어 sem_two를 이용한 wait과 post 함수의 호출이다.
		// 이는 accu 함수를 ㅎ출하는 쓰레드가 값을 가져가지도 않았는데,
		// read 함수를 호출하는 쓰레드 값응 다시 가져다 놓은 상황을 막기 위한 것이다.
		sem_wait(&sem_two);
		scanf("%d", &num);

		//  키를 반납 세나포어 1에 키가 1증가
		sem_post(&sem_one);
	}
	return NULL;
}

// 결과
void * accu(void * arg)
{
	int sum = 0, i;
	for(i=0; i<5; i++)
	{
		// 세나포어 1에서 키를 획득 세나포어 2의 키가 -1감소
		sem_wait(&sem_one);
		sum+=num;

		// 세나포어 2에 키를 반납 세나포어 1의 키가  +1증가
		// 세마포어 sem_two를 이용한 wait과 post 함수의 호출이다.
                // 이는 accu 함수를 ㅎ출하는 쓰레드가 값을 가져가지도 않았는데,
                // read 함수를 호출하는 쓰레드 값응 다시 가져다 놓은 상황을 막기 위한 것이다.
		sem_post(&sem_two);
	}
	printf("Result: %d \n", sum);
	return NULL;
}
