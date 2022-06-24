#define F_CPU	7372800UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd.h"

// 문자 출력
int main()
{
	Byte str1[] = "LCD TEST";
	Byte str2[] = "ATmega128";
	DDRA = 0xff;
	DDRG = 0x0f;
	
	Lcd_Init();
	while(1){
		
		Lcd_Pos(0, 0);
		Lcd_STR(str1);
		Lcd_Pos(1, 0);
		Lcd_STR(str2);
	}
	
	return 0;
}


//// 곱하기
//int main()
//{
	//DDRA = 0xff;
	//DDRG = 0x0f;
	//Byte str1[13];
	//
	//Lcd_Init();
	//while(1){
		//for(int i = 2; i<=9; i++){
			//for(int j = 1; j<=9; j++){
				//Lcd_Pos(0, 0);
				//sprintf(str1, "%d * %d = %d", i, j, i*j);
				//Lcd_STR(str1);
				//_delay_ms(1000);
			//}
		//}
	//}
	//
	//return 0;
//}