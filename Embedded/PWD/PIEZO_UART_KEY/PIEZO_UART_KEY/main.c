#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int DoReMi[8] = {523, 587, 659, 698, 783,880, 987, 1046};

void putch(unsigned char data)
{
	while((UCSR0A & 0x20) == 0);	//UDRE0 : 전송 준비가 되면 1인 비트(0x20), 전송준비 되기 전까지 대기
	UDR0 = data;					//UDR0 : H - 수신된 데이터 저장, L - 전송될 데이터 저장
	UCSR0A |= 0x20;					//UDRE0 비트
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80) == 0);	//RXC0 : 데이터 받으면 1인 비트(0x80), 데이터 받을 때까지 대기
	//while(RXC0 == 0);	//RXC0 : 데이터 받으면 1인 비트(0x80), 데이터 받을 때까지 대기
	data = UDR0;					//UDR0 : H - 수신된 데이터 저장, L - 전송될 데이터 저장
	UCSR0A |= 0x80;					//RXC0 비트
	
	return data;
}

void putStr(char *str)
{
	while(*str != 0)
	{
		putch(*str);
		str++;
	}
}

int main()
{
	unsigned char piano = 0;
	unsigned char tmpCh = 0;
	DDRE = 0xFE;			// Rx(입력 0), Tx(출력 1)
	DDRB = 0x80;			// pin7 출력
	
	//UART 설정
	UCSR0A = 0x00;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) ;			// Rx, Tx Enable / 0x18
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);			// 비동기방식(UMSEL0 = 0), NoParityBit(UPM01 = 0, UPM00 = 0), 1 Stop Bit / 0x06
	
	UBRR0H = 0x00;
	UBRR0L = 0x03;
	
	putStr("\rLet's go~\n");
	
	//Fast PWM(모드 14) 설정
	TCCR1A = (1 << COM1C1) | (1 << WGM11);
	TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);		//Clear OCnA/OCnB/OCnC on compare match	(low level에서 출력)
	TCCR1C = 0x00;
	TCNT1 = 0x00;	//타이머 1 값 초기화
	
	OCR1C = 0;
	
	while(1)
	{
		tmpCh = getch();
		
		if(('0'<tmpCh) && (tmpCh<'9'))
		{
			piano = tmpCh - '0';
			putch(tmpCh);
			putch('\n');
			putch('\r');
			ICR1 = 7372800/DoReMi[piano-1];
			OCR1C = ICR1/16;
			_delay_ms(500);
			OCR1C = 0;

		}
		else
		{
			putStr("\rPress 1 ~ 8\n");
		}
	}
	
}