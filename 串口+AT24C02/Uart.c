#include <REGX52.H>

void UART_Init(){
	SCON=0x50;
	PCON=0x80;
	TMOD&=0x0F;
	TMOD|=0x20;
	TR1=1;
	TH1=0xF4;
	TL1=0xF4;
	ET1=0;
	TI=0;
	RI=0;
	EA=1;
	ES=1;

}

void Uart_SendByte(unsigned char byte){
	SBUF=byte;
	while(TI==0);
	TI=0;
}