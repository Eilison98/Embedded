#define F_CPU 7432800UL
#include <avr/io.h>     // AVR 입출력에 대한 헤더 파일
#include <util/delay.h> // delay 함수사용을 위한 헤더파일

int main(void)
{
	// 7-Segment 에 표시할 글자의 입력 데이터를 저장
	unsigned char FND_DATA_TBL [] = {0x3F,0X06,0X5B,0X4F,0X66,0X6D,
								     0X7C,0X07,0X7F,0X67,0X77,0X7C,
								     0X39,0X5E,0X79,0X71,0X08,0X80};
	
	// FND Table 카운터 변수								 
    unsigned char cnt=0;
	
	// 포트A 를 출력포트로 설정
    DDRA = 0xFF;
	
	while(1)
	{
		//  포트 A 에 FND_DATA_TBL 값을 출력
		PORTA = FND_DATA_TBL[cnt];
		
		//  FND_DATA_TBL 카운터 변수를 증가
		cnt++;
		
		//  테이블 크기를 초과하는 경우를 방지
		if(cnt>9) cnt = 0;
		
		//  500ms 시간 지연
		_delay_ms(500);
	}
}

