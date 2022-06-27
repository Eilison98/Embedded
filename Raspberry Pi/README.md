# Raspberry Pi 공부 정리

<br/>

## Raspberry Pi
- GPIO 입출력 제어
- 인터럽트
- 타이머 / 카운터 8Bit
- 타이머 / 카운터 16Bit
- PWD
- PIEZO
- UART
- MOTER

## AVR 마이크로 컨트롤러의 입출략 포트
- 입출력 포트 제어용 레지스터
  - DDRx 레지스터
    - 입출력의 방향설정을 하기 위한 레지스터
    - DDRA ~ DDRG 레지스터의 해당 비트에 '1'을 쓰면 출력, '0'을 쓰면 입력으로 설정
  - PORTx 레지스터
    - 데이터 출력용 레지스터
    - 출력을 원하는 데이터 값을 PORTx 레지스터에 넣어줌
  - PINx 레지스터
    - 데이터 입력용 레지스터
    - PINx 레지스터에 해당하는 값을 읽으면 해당 핀의 값을 읽음
  - SFIOR 레지스터
    - Special Function IO Register
    - AVR 입출력 포트의 특수 기능을 제어하기 위한 레지스터
    - SFIOR의 비트2 ( PUD" Pull-Up Disable )를 '1'로 세트하면 풀업 저항을 비활성화

<br/>
