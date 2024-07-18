#include<p18f4520.h>
#include<delays.h>

#pragma config OSC = HS
#pragma config MCLRE = ON
#pragma config WDT = OFF
#pragma config PBADEN = OFF
#define PB1 PORTBbits.RB1

const unsigned char LED7[] = {0x40, 0xf9, 0x24, 0x30, 0x19, 0x12, 0x02, 0xf8, 0x00, 0x10};
int dem = 0;

void ngat_ngoai (void);
#pragma code ngat_ngoai_cao = 0x08
void ngat_cao (void)
{
	ngat_ngoai ();
}
#pragma code
#pragma interrupt ngat_ngoai
void ngat_ngoai (void)
{
	if (INTCON3bits.INT1IF)
	{
		INTCON3bits.INT1IF = 0;
		dem ++;
	}
}

void main (void)
{
	TRISB = 0x02;
	TRISD = 0x00;
	INTCONbits.GIE = 1;
	INTCON3bits.INT1IE = 1;
	INTCON2bits.INTEDG1 = 0;
	
	while (1)
	{
		if (dem > 9)
		{
			dem = 0;
		}
		else
		{
			PORTD = LED7[dem];
		}
	}
}