#include <REGX52.H>
#include "Delay.h"

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

void I2C_Start(){
	I2C_SCL=1;
	I2C_SDA=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

void I2C_Stop(){
	I2C_SDA=0;
	I2C_SCL=1;
	I2C_SDA=1;
}

void I2C_SendByte(unsigned char Byte){
	unsigned char i;
	for(i=0;i<8;i++){
		if(Byte&(0x80>>i)){I2C_SDA=1;}
		else if((Byte&(0x80>>i))==0){I2C_SDA=0;}
		I2C_SCL=1;
		I2C_SCL=0;
	}
}

unsigned char I2C_ReceiveByte(){
	unsigned char i, Byte=0x00;
	I2C_SDA=1;
	for(i=0;i<8;i++){
		I2C_SCL=1;
		if(I2C_SDA){Byte|=(0x80>>i);}
		I2C_SCL=0;
	}
	return Byte;
}

void I2C_SendAck(bit Ack){
	I2C_SDA=Ack;
	I2C_SCL=1;
	I2C_SCL=0;
	
}

unsigned char I2C_ReceiveAck(){
	unsigned char Ack;
	I2C_SDA=1;
	I2C_SCL=1;
	Ack=I2C_SDA;
	I2C_SCL=0;
	return Ack;
}
