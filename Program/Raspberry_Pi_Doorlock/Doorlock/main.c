/*
 * Program_DoorLock.c
 *
 * Created: 2022-06-24
 *  Author: 임성수
 */ 

#define F_CPU 7372800UL
#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>
#include "Lcd.h"

unsigned char keyscan();

void UART_Condition()
{
	DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	
	UBRR0H = 0x00;
	UBRR0L = 3;
}
void init_keypad()
{
	DDRA = 0xF8; //0b 1111 1000
	PORTA = 0x07; //0b 0000 0111
}
void putch(unsigned char data)
{
	while((UCSR0A & 0x20)==0);
	UDR0 =data;
	UCSR0A |=0x20;
}

unsigned char Step[8] = {0x90,0x80,0xC0,0x40,0x60,0x20,0x30,0x10};

int main()
{
	//4자리 비밀번호 설정
	//키패드에 비밀번호 입력 이때 번호는 ****모양
	//비밀번호가 맞으면 스탭모터로 문열림
	//비밀번호가 틀리면 LCD창에 ERROR NUMBER 및 부저음 발생
	//인터럽트 버튼을 누르면 비밀번호 입력
	
	unsigned char text[] = "\r\n Insert Password : ";
	// 부저음
	unsigned int DoReMi[8] = {523,587, 659, 698, 783,880, 987, 1046};
	unsigned char piano=0;
	UART_Condition();
	init_keypad();
	unsigned int i =0;
	unsigned char j, t = 0;	// 모터
	unsigned char Password[4];
	unsigned char Old_Password[4]= {'1','2','3','4'};
	int press = 0;
	
	// Step Motor 문열기
	DDRB = 0x20; // MOTOR1_EN 를 출력 포트로 설정 0b 0010 0000
	DDRD = 0xF0; // STEP0 ~ STEP3을 출력 포트로 설정
	//PORTB &= ~0x20; // M1 Disable, DC 모터 정지
	
	//부저
	DDRB |= 0x80; // PWM 출력, OCR1C 0b 1010 0000
	TCCR1A |= 0x0A; // COM1C(1:0)=“10”, OC1C핀사용, WGM3(1:0)=“10”
	TCCR1B |= 0x19; // WGM3(3:2)=“11”, CS3(2:0)=“001” 1분주 사용
	TCCR1C = 0x00; // WGM3(3:0)=“1110”, Fast PWM, 모드 14
	TCNT1 = 0x0000; // 타이머1 카운터 초기화
	
	//LCD로 OPEN 출력
	DDRC = 0xff;
	DDRG = 0x0f;
	Byte *str = " OPEN ";
	Lcd_Init();
	Lcd_Clear();

	while(1)
	{
		while(text[i] !='\0')
		{
			putch(text[i++]);	//비밀번호 입력하시오.
		}
		i=0;
		while (1)
		{
			//누르고 있는 상태 - 1, 떨어진 상태 - 0
			if(i >= 4) break;
			unsigned char input = keyscan();
			if (input == 0)
			{
				press = 0;
			}
			if (input != 0)
			{
				if (press)
				{
					continue;
				}
				unsigned char key = input; //keysca n을 통해 받는 값을 key 에 저장
				Password[i] = key;	// key 값을 하나씩 Password 배열에 저장하며 비밀번호 설정
				press = 1;
				i++;
				putch('*');
			}
		}
		for(int i=0; i<4; i++)
			putch(Password[i]);
		putch('\r'); putch('\n');
		for(int i=0; i<4; i++)
			putch(Old_Password[i]);
		putch('\r'); putch('\n');
		while(1)
		{
			//if (Password[4] = "####") // 반복문을 탈출하며 비밀번호 재설정
			//{
				//break;
			//}
			int fault = 0;
			for (i=0; i<4; i++)
			{
				if (Password[i] != Old_Password[i])
				{
					fault = 1;
					break;
				}
			}
			if (!fault) // 입력한 비밀번호가 원래 비번하고 같으면 
			{
				putch('d');
				for ( j = 0; j < 48 ; j++ )
				{
					PORTD = Step[t]; // 한 스텝 실행
					t++; // 다음 스텝 실행을 위해 t 증가
					if(t > 7) t = 0; // 8 스텝을 초과하지 않도록 초기화
					_delay_ms(10);
				}
				//Lcd에 OPEN 출력
				Lcd_Pos(0,0);
				Lcd_STR(str);
				
				//열리는 부저 
				for (i = 0; i < 9; i++)
				{
					ICR1 = 7372800/DoReMi[piano]; // 버튼에 맞는 음향을 연주
					OCR1C = ICR1/4; // 50% 듀티비
					piano++; // piano 변수 1증가
					if(8 < piano) piano = 0; // piano가 9가 되면 초기화
					_delay_ms(100);
				}
				
				break;
			}
			else
			{
				//틀렸다는 부저
				for (i=0; i<4; i++)
				{
						
				}
			}
		}
	}
	return 0;
}

unsigned char getch()
{
	unsigned char data;
	while((UCSR0A & 0x80)==0);
	data = UDR0;
	UCSR0A |= 0x80;
	return data;
}

unsigned char keyscan(void)
{
	PORTA = 0x08;
	_delay_ms(1);
	if(PINA&0x01) return '1';
	if(PINA&0x02) return '2';
	if(PINA&0x04) return '3';
	PORTA = 0x00;
	_delay_ms(10);
	
	PORTA = 0x10;
	_delay_ms(1);
	if(PINA&0x01) return '4';
	if(PINA&0x02) return '5';
	if(PINA&0x04) return '6';
	PORTA = 0x00;
	_delay_ms(10);
	
	PORTA = 0x20;
	_delay_ms(1);
	if(PINA&0x01) return '7';
	if(PINA&0x02) return '8';
	if(PINA&0x04) return '9';
	PORTA = 0x00;
	_delay_ms(10);
	
	PORTA = 0x40;
	_delay_ms(1);
	if(PINA&0x01) return '*';
	if(PINA&0x02) return '0';
	if(PINA&0x04) return '#';
	PORTA = 0x00;
	_delay_ms(10);
	
	return 0;
}