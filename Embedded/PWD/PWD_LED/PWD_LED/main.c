#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char Light = 0;
	
	// 포트B 를 출력포트로 설정
	DDRB = 0x10;
	
	// 타이머/카운터 제어 레지스터(TCCRn)
	// PC PWM 모드, 1024 분주 ==> 14.4 KHz :
	TCCR0 = 0x77;
	
	// 타이머/카운터 레지스터(TCNTn)
	// 타이머0 카운터를 초기화
	TCNT0 = 0x00;
	
	while (1)
	{
		for(Light=0;Light<255;Light++)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
		for(Light=255;0<Light;Light--)
		{
			OCR0 = Light;
			_delay_ms(10);
		}
	}
}
