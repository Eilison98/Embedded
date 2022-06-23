#define F_CPU 7432800UL
#include <avr/io.h>
#include <util/delay.h>

int Count_TR(unsigned char flag);

int main(void)
{
	// 7-Segment 에 표시할 글자의 입력 데이터를 저장
	unsigned char FND_DATA_TBL []={0x3F,0X06,0X5B,0X4F,0X66,0X6D,
							       0X7C,0X07,0X7F,0X67,0X77,0X7C,
								   0X39,0X5E,0X79,0X71,0X08,0X80};
	
	// FND Table 카운터 변수							   
	unsigned int cnt=0;
	
	// 스위치 값 저장 변수
	unsigned char Switch_flag = 0;
	
	DDRA = 0xFF; // 포트A 를 출력포트로 설정
	DDRE = 0x00; // 포트E 를 입력포트로 설정
	
	while (1) {
		// 입력핀이 포트 E 의 상위 비트이므로 우측으로 4비트 쉬프트
		Switch_flag = PINE >> 4;
		while(PINE >> 4 != 0x00); // 스위치를 눌렀을 경우 땔 때까지 대기
		if(Switch_flag != 0)// 스위치가 눌렀을 경우에 만 실행
		// 스위치 튼에 따라 변수 cnt 값을 증가 또는 감소
		cnt += Count_TR(Switch_flag);
		// 변수 cnt 값의 범위를 0 ~ 15로 설정
		if(cnt < 0)
		cnt = 0;
		else if(cnt > 15)
		cnt = 15;
		PORTA = FND_DATA_TBL[cnt]; // 포트 A 에 FND Table 값을 출력
		_delay_ms(100); // 100ms 시간 지연
	}
}

// 스위치 누른 상태에 따라 증감 감소를 값을 반환하는 함수
int Count_TR(unsigned char flag) {
	int count = 0;
	switch (flag) {
		case 0x01: // SW0을 눌렀을때
		count = 1;
		break;
		case 0x02: // SW1을 눌렀을때
		count = 2;
		break;
		case 0x04: // SW2을 눌렀을때
		count = -1;
		break;
		case 0x08: // SW3을 눌렀을때
		count = -2;
		break;
	} return count;
}