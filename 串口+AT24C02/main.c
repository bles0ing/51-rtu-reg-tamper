#include <REGX52.H>
#include "Uart.h"
#include "AT24C02.h"
#include "Delay.h"
#include <string.h>
#include "Timer0_Init.h"

unsigned char found=0,i=0;
unsigned char rfx_list[20],num_list[4];
unsigned char count=0,temp=0,num_count=0;
char ch;
unsigned short time_count=0;

void main(){

	UART_Init();
	Timer0_Init();
	while(1){
		if(found==1){
			ES = 0; 
			Uart_SendByte(AT24C02_ReadByte(0));
			Uart_SendByte(AT24C02_ReadByte(1));
			Uart_SendByte(AT24C02_ReadByte(2));
			Uart_SendByte(AT24C02_ReadByte(3));
			found=0;
			ES = 1; 
		}
		else if(found==2){
			while(num_count!=4);
			num_count=0;
			for(i=0;i<4;i++){
				AT24C02_WriteByte(i,num_list[i]+0x30);
				Delay(10);
			}
			found=0;
		}
		if(time_count>=1000 && count>0){
			rfx_list[count]='\0';
			if(strcmp(rfx_list,"READ")==0){
				found=1;
			}
			else if(strcmp(rfx_list,"SET")==0){
				found=2;
			}

			count=0;
			time_count=0;
		}
	}
}

void UART_Routine() interrupt 4{
	if(RI){
		RI=0;
		ch=SBUF;
		if(found==2){
			num_list[num_count]=SBUF;
			Uart_SendByte(SBUF);
			num_count++;
		}
		else if(ch!='\r' && ch!='\n' && found!=1){
			Uart_SendByte(ch);
			rfx_list[count]=ch;
			count++;
			}
		time_count=0;
	}
	else{
		while(!TI);
		TI=0;
	}
	
}

void Timer0_Routine() interrupt 1{
	TH0=0xFC;
	TL0=0x18;
	time_count++;
}