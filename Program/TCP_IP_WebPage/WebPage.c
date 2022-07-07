#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void error_handling(char *message);

char webpage[] = "HTTP/1.1 200 OK\r\n"
 		 "Server:Linux Web Server\r\n"
		 "Content-Type: text/html; charset=UTF-8\r\n\r\n"
		 "<!DOCTYPE html>\r\n"
		 "<html><head><title> My Web Page </title>\r\n"
		 "<style>body {background-color: #FFFF00 }</style></head>\r\n"
		 "<body><center><h1>Web Program</h1><br>\r\n"
		 "<img src=\"beach.jpg\"></center></body></html>\r\n";

int main(int argc, char *argv[])
{
	// 소켓 서버
	int serv_sock;

	// 클라이언트 서버
	int clnt_sock;

	int fdimg;
	char img_buf[700000];

	// 버퍼 크기
	char buf[1024];

	// 서버
	struct sockaddr_in serv_addr;

	// 클라이언트
	struct sockaddr_in clnt_addr;

	// 클라이언트 소켓의 주소 크기
	socklen_t clnt_addr_size;

	if(argc!=2)
	{
		printf("Usage : %s <port>/n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	// 소켓 예외 처리
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	// 바인드 예외 처리
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error");

	// 리슨 예외 처리
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	// 연결 예외 처리
	if(clnt_sock==-1)
		error_handling("accept() error");

	while(1)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
		puts("New client connection......");

		read(clnt_sock, buf, 1024);
		printf("%s\n", buf);

		if(!strncmp(buf, "GET /beach.jpg", 14))
		{
                	fdimg = open("beach.jpg", O_RDONLY);
	                read(fdimg, img_buf, sizeof(img_buf));
	                write(clnt_sock, img_buf, sizeof(img_buf));

	                close(fdimg);
        	}
        	else
                	write(clnt_sock, webpage, sizeof(webpage) - 1);
	        puts("closing.....");
		close(clnt_sock);
	}
	close(serv_sock);
	return 0;
}

// 예외처리 출력문자
void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
