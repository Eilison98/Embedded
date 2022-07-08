#define F_CPU 7432800UL
#include <avr/io.h> // AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h> // AVR 인터럽트에 대한 헤더파일

volatile unsigned char LED_Data = 0x00;
unsigned char timer0Cnt=0;
SIGNAL(TIMER0_OVF_vect); // Timer0 Overflow0 ISP

int main(void) {
	DDRC = 0x0F; // 포트C 를 출력포트로 설정
	TCCR0 = 0x07;
	TCNT0 = 112; // 256-144=112 -> 0.01초 마다 한번씩 인터럽트 발생
	TIMSK = 0x01;
	TIFR |=1 << TOV0;
	sei();  // 전체 인터럽트를 허용
	
	while (1)
    {
		// 포트C로 변수 LED_Data에 있는 데이타 출력
		PORTC = LED_Data;
	}
}

SIGNAL(TIMER0_OVF_vect) 
{
	cli();  // 전체 인터럽트를 금지
	
	// 256-144=112 -> 0.01초 마다 한번씩 인터럽트 발생
	TCNT0 = 112;
	
	// timer0Cnt 변수를 1 증가
	timer0Cnt++;
	
	// 0.01s*100=1s를 얻기 위한 카운트 횟수
	if(timer0Cnt == 100) 
	{
		// LED_Data 변수를 1 증가
		LED_Data++;
		if(LED_Data>0x0F) LED_Data = 0;
		timer0Cnt = 0;
	}
	sei();  // 전체 인터럽트를 허용
}