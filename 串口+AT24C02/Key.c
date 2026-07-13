#include <REGX52.H>
#include "DELAY.H"


unsigned char Key(){
	unsigned int Keynum=0;
	if (P3_0==0){Delay(20);while(P3_0==0);Delay(20);Keynum=1;}
	if (P3_1==0){Delay(20);while(P3_1==0);Delay(20);Keynum=2;}
	if (P3_2==0){Delay(20);while(P3_2==0);Delay(20);Keynum=3;}
	if (P3_3==0){Delay(20);while(P3_3==0);Delay(20);Keynum=4;}
	return Keynum;
}