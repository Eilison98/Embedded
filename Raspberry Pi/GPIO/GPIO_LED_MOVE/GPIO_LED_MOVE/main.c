#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    unsigned char LED_Data = 0x01, i;
	DDRC = 0x0F;  //  포트C 를 출력포트로 설정
	while(1)
	{
		//  변수 LED_Data에 초기값 0x01로 저장
		PORTC = LED_Data;
		
		//  LED0 ~ LED3으로 이동
		for(i=0; i<4; i++)
		{
			//  포트C 로 변수 LED_Data에 있는 데이터 출력
			PORTC = LED_Data;
			
			// 좌측 쉬프트 연산자를 이용
			LED_Data <<= 1;
			
			//  ms 단위의 딜레이 함수
			_delay_ms(1000);
		}
	}
}

