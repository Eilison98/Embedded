#define F_CPU 7372800UL
#include <avr/io.h> // AVR 입출력에 대한 헤더 파일
#include <util/delay.h> // delay 함수사용을 위한 헤더파일

int main(void)
{
	unsigned char i;
	
	DDRB = 0x20;    //  MOTOR1_EN 를 출력 포트로  설정
	DDRD = 0xF0;    //  STEP0 ~ STEP3을 출력 포트로 설정
	PORTB &= ~0x20; //  M1 Disable, DC 모터 정지
	
	while(1)
	{
		for ( i = 0; i < 12; i++ )  // 48 스텝 실행
		{
			PORTD = 0x30;     // STEP 1
			_delay_ms(100);
			PORTD = 0x90;     // STEP 2
			_delay_ms(100);
			PORTD = 0xC0;     // STEP 3
			_delay_ms(100);
			PORTD = 0x60;     // STEP 4
			_delay_ms(100);
		}
		_delay_ms(1000);      //  한바퀴 회전 후 1초간 대기
	}
}

