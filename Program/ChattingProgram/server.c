//  표준 라이브러리 함수
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

//  최대인원
//  Max_Person
#define CLNT_MAX 10

//  글로벌 클라이언트 소켓
//  Gobal_Client Socket
int g_clnt_socks[CLNT_MAX];

//  클로벌 클라이언트 카운드
int g_clnt_count = 0;

int main(int  argc, char ** argv)
{
	//  소켓 서버
	//  server socket
	int serv_sock;

	//  클라이언트 서
	//  clint socket
	int clnt_sock;

	//  클라이언트 주소의 사이즈
	int clnt_addr_size;

	//  클라이언트 의 고객주소나 IP가 담긴다.
	struct sockaddr_in clnt_addr;

	//  서버
	struct sockaddr_in serv_addr;

	//  serv_sock 안에 소켓의 (네트워크 주소 체계와, 소켓타입, 프로토콜)을 저장한다.
	//  마지막에 0은 소켓타입을 따라간다는 것이다.
	//  IPv4, Transmission Method =  TCP, Protocol 0 = Follow in Front (ex. SOCK_STREAM = TCP)
	serv_sock  = socket(PF_INET, SOCK_STREAM, 0);

	//  serv_addr.sin_family(주소타입)에 네트워크 주소 체게입력
	//  PF_INET(protocol) = AF_INET(addr)는 같은 네크워크 주소인 IPv4 이지만
	//                      암묵적인 룰로 프로토콜타입과 주소타입으로  각각 다르게 입력한다.
	//  PF_INET(protocol) = AF_INET(addr)  //  IPv4
	serv_addr.sin_family = AF_INET;

	//                        NETWORK ORDER  /  네트워크 오더
	//  호스트를 네트워크방식의 빅엔디안으로 변경한다. 롱으로 32비트
	//  INADDR_ANY는 현재 컴퓨터의 아이피 주소값을 말한다.
	//  Socket bind Address = host to network long(Now Pc IP)
	//                     host -> network method Change by BigEndian = 32bit
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        //                        NETWORK ORDER  /  네트워크 오더
	//  호스트를 네트워크방식의 빅엔디안으로 변경한다. 숏으로 16비트
	//  Socket bind Port    = host to network sort
	//                     host -> network method change bt BigEndian = 16bit
	//  atoi = character ->  integer
	serv_addr.sin_port = htons(7989);

	//  sockaddr는 소켓의 주소를 담는 기본 구조체 역활을 한다.
	//  바인드에 (서버소켓, serv_addr의 주소값, serv_addr의사이즈 == 에러시)
	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
	{
		//  바인드에서 에러가 났다고 호출
		printf("Bind Error\n");
	}

	// 리슨에  (서버소켓, 대기인원) == 에러시
	if(listen(serv_sock, 5) == -1)
	{
		//  리슨에서 에러가 났다고  호출
		printf("Listen Error\n");
	}

	//  버퍼크기
	char buff[200];

	//  얼마만큼 받아왔는
	int recv_len = 0;

	//  반복문
	while(1)
	{
		clnt_addr_size = sizeof(clnt_addr);

		//  한명당 생성되는 클라이언트 소켓  ,  accept로 반환
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

		//  글로벌 클라이언트 소켓에 한명이 들어왔으므로 1증가 = 서버에 있는 클라이언트 소켓을 넣는다.
		//  g_clnt_socks[g_clnt_count++] = clnt_sock;

		while(1)
		{
		//  얼마만큼 받아왔는지 = 클라이언트 소켓을 통해서 읽고, 받아올 데이터 넣는곳 , 최대 사이즈 200
			recv_len = read(clnt_sock, buff, 200);

			printf("Client recv : ");

			//  받은 데이터의 길이만큼 증가
			for(int i = 0; i < recv_len; i++)
			{
				//  버퍼에 저장된 데이터를 순서대로 출력한다 ( 대문자로 )
				printf("%02X ",(unsigned char)buff[i]);
			}
			//  엔터
			printf("\n");
		}
	}
}
