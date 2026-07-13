#include <REGX52.H>
#include <INTRINS.H>
void Delay(x)		//@11.0592MHz
{
	unsigned char i, j;
	while (x--){
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
