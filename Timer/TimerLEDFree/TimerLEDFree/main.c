#define F_CPU 7432800UL
#include <avr/io.h> // AVR 입출력에 대한 헤더 파일
#include <avr/interrupt.h> // AVR 인터럽트에 대한 헤더파일

volatile unsigned char LED_Data = 0x00;
unsigned int timer0Cnt=0;
SIGNAL(TIMER0_OVF_vect); // Timer0 Overflow0 ISP

int main(void)
{
    DDRC = 0x0F; // 포트C 를 출력포트로 설정
    TCCR0 = 0x06; // 프리스케일러 256
    // 256-144=112 -> 0.0025초 마다 한번씩 인터럽트 발생
    TCNT0 = 112;
    TIMSK = 0x01;
    TIFR |=1 << TOV0;
	
	sei();
	while (1)
	{
		PORTC = LED_Data; // 포트C로 변수 LED_Data에 있는 데이타를 출력
	} return 0;
}

SIGNAL(TIMER0_OVF_vect)
{
	cli();
	// 256-144=112 -> 0.0025초 마다 한번씩 인터럽트 발생
	TCNT0 = 112;
	timer0Cnt++; // timer0Cnt 변수 1 증가
	// 0.0025s * 400 = 1s, 1초를 얻기 위한 카운트 횟수
	if(timer0Cnt == 400)
	{
		LED_Data++; // LED_Data 변수 1 증가
		if(LED_Data>0x0F) LED_Data = 0;
		timer0Cnt=0;
	} sei();
}


