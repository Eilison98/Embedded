#define F_CPU 7432800UL
#include <avr/io.h>

int main(void)
{
	DDRC = 0x0F; // 포트C 를 출력포트로 설정
	DDRE = 0x00; // 포트E 를 입력포트로 설정
	while (1)
	{
		PORTC = PINE >> 4; // 포트 E 로 입력받은 값을 포트C로 출력
		                   // 입력핀이 포트 E 의 상위 비트이므로 우측으로 4비트 쉬프트
	}
}

