#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

//  버퍼의  크기
#define BUFFSIZE 100

//  이름의 크기
#define NAMESIZE 20

int StoHEX(char fi, char sc);
void error_handling(char *msg);
void * send_message(void * arg);
void * recv_message(void * arg);

//  입력할 메시지?
char message[BUFFSIZE];

void * rcv(void * arg)
{
	printf("Rcv Thread Created\n");
	int sock = (int)arg;
	char buff[500];
	int len;
	while(1)
	{
		len = read(sock, buff, sizeof(buff));

		if(len == -1)
		{
			printf("sock close\n");
			break;
		}

		printf("%s", buff);
	}
	pthread_exit(0);
	return 0;
}

int main(int argc, char **argv)
{
	//  소켓 서버
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t rcv_thread;
	void* thread_result;

	char id[100];

	if(argc < 2)
	{
		printf("You have to Enter ID\n");
		return 0;
	}
	strcpy(id, argv[1]);
	printf("id : %s\n", id);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		printf("socket error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(7989);

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("Connect error");
	}
	else
	{
		printf("connection success\n");
	}

	pthread_create(&rcv_thread, NULL, rcv, (void *)sock);

	char chat[100];
	char msg[1000];

	printf("while before\n");
	while(1)
	{
		//  안내문구
		printf("채팅 입력 : ");

		//  채팅을 받는다.
		gets(chat);

		//  아이디, 
		sprintf(msg, "[%s] : %s\n", id, chat);

		printf("send : %s", msg);
		write(sock, msg, strlen(msg)+1);
		sleep(1);
	}

	printf("while before\n");
	close(sock);
	return 0;
}
