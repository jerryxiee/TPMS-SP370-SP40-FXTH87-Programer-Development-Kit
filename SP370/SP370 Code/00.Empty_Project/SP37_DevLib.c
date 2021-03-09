/* ****************************************************************************************************/
/*                             Development Library Functions for SP37 Application Development         */
/*   -----------------------------------------------------------------------------------------------  */
/*                                                                                                    */   
/*   Purpose: 	 Software UART, Automatic Register Configurations,...								  */
/*                                                                                                    */
/*                                                                                                    */
/*   Filename:   SP37_DevLib.c                                                                        */
/*                                                                                                    */
/*   Target:     SP37                                                                                 */
/*                                                                                                    */
/*   Dev. Envir: Keil Software C51 V7.10                                                              */
/*               µVision2 V2.40                                                                       */
/*   Author:     TL	                                                 	   		                      */
/*                                                                     	                              */
/*   History:    30.July 2008: First Release				                                          */
/*				 							                                                          */				 
/*                                                                                                    */
/*   Status:     Release V1.0                                                                         */
/* ************************************************************************************************** */
/*  (C)opyright Infineon Technologies AG. All rights reserved.                                        */
/* ****************************************************************************************************/
  
/**********************************************************************************
 Includes 
***********************************************************************************/
#include "Reg_SP37.h"
#include "SP37_DevLib.h"

/**********************************************************************************
 Initializes Ports 
***********************************************************************************/
void RS232_Init(unsigned char Tx, Rx)
{
	P1DIR &= ~(Tx);					// Set PP2 to Output
	P1OUT |= Tx;					// TX to IDLE	
	P1DIR |= Rx;					// Set PP1 to Input
	GPR0   = 0;						// Clear GPR0... <- This holds information about Input/OutPut
	GPR0   = ((Tx<<4) | (Rx));		// GPR0		TxPP   RxPP
									// 			xxxx | xxxx 
}

/**********************************************************************************
 Un- Initializes Ports 
***********************************************************************************/
void RS232_UnInit(unsigned char Tx, Rx)
{
	P1DIR |= (Tx | Rx);				// Set needed Pins to Input again
}

/**********************************************************************************
 Converts from HEX -> ASCII and transmits to UART 
***********************************************************************************/
void RS232_Send_Hex (unsigned char Byte)
{
	unsigned char Nibble;
	
	Nibble = (Byte >> 4) + 0x30;
	if ( Nibble > 0x39)
		Nibble += 7;
	putchar (Nibble);
	Nibble = (Byte & 0x0F) + 0x30;
	if ( Nibble > 0x39)
		Nibble += 7;
	putchar (Nibble);
}

/**********************************************************************************
 Transmits number of "bits" of a value "dat"  - MSB first
***********************************************************************************/
void RS232_Send_Bin(char dat, char bits)
{
	int i;
	for(i=bits;i>0;i--)
	{
		if ( dat & ( 1<<(i-1) ) )
			putchar('1');
		else
			putchar('0');
	}
}

/**********************************************************************************
 Sends one character to UART
***********************************************************************************/
char putchar (char Result)
{
	unsigned char i;
	unsigned char TMOD_old, TL0_old, TH0_old;

	// SAVE olf Timer Registers 
	TMOD_old = TMOD;
	TL0_old = TL0;
	TH0_old = TH0;

	TMOD = 0x12;		// Set up Timer Mode 2 and systemclock/8 as timebase

	// CONFIGURE Timer Values for actual system clock SFR
	if (DSR & 0x80)		// IF CRYSTAL IS USED DETERMINE CRYSTAL FREQ AND SET TIMER
	{
		#ifdef _19687500_Crystal_315MHz		
			TL0 = 0x40;
			TH0 = 0x40;
		#endif

		#ifdef _18080000_Crystal_433_92MHz
			TL0 = 0x3B;
			TH0 = 0x3B;
		#endif
	}	

	else 								// IF RC-HF IS USED USE DEFAULT VALUES	 
	{
			TL0 = 0x4E;
			TH0 = 0x4E;
	}

	// START Bit
	P1OUT &= ~(GPR0>>4);				// Set Tx Bit = 0
	T0RUN = 1;							// Start Timer0
	IDLE = 1;							// Wait for a timer event before starting transmission
	T0FULL = 0;							// Write to Timer full event flag to reset it
	
	// DATA Bit [7:0]			   
	for (i=0; i < 8; i++)
	{
		if (Result & 0x01)
			P1OUT |= (GPR0>>4);			// Set Tx Bit = 1
		else
			P1OUT &= ~(GPR0>>4);		// Set Tx Bit = 0
		Result >>= 1;					// Shift Result one bit left to prepare next bit
		IDLE = 1;						// Wait for a timer event before starting transmission
		T0FULL = 0;						// Write to Timer full event flag to reset it
	}

	// STOP Bit
	P1OUT |= (GPR0>>4);					// Set Tx Bit = 1
	IDLE = 1;							// Wait for a timer event before starting transmission
	T0FULL = 0;							// Write to Timer full event flag to reset it
	T0RUN = 0;							// Stop Timer0

	// RESTORE old Timer SFR values
	TMOD = TMOD_old;
	TH0 = TH0_old;
	TL0 = TL0_old;
	
	return Result;
}

/**********************************************************************************
 Reads one character from UART
***********************************************************************************/
char getchar (void)
{
	unsigned char i; 
	unsigned char Character = 0;
	unsigned char TMOD_old, TL0_old, TH0_old;
	
	// SAVE olf Timer Registers 
	TMOD_old = TMOD;
	TL0_old = TL0;
	TH0_old = TH0;

	TMOD = 0x12;					// Set up Timer Mode 2 and systemclock/8 as timebase
    
	if (DSR & 0x80)	  				// IF CRYSTAL IS USED DETERMINE CRYSTAL FREQ AND SET TIMER
	{
		#ifdef _19687500_Crystal_315MHz		
			TL0 = 0x60;
			TH0 = 0x40;
		#endif

		#ifdef _18080000_Crystal_433_92MHz
			TL0 = 0x59;
			TH0 = 0x3B;
		#endif
	}
	
	else 							// IF RC-HF IS USED USE DEFAULT VALUES	 
	{
			TL0 = 0x75;
			TH0 = 0x4E;
	}

	while (P1IN & (GPR0 & 0x0F))		// Wait for a high to low transition on PP1 (RX)
	{
		WDRES = 1;						// Reset Watchdog timer while waiting
	}

	T0RUN = 1;							// Start timer 0 with 1,5* Bitperiod
	IDLE = 1;							// Wait for a timer event before starting reseption
	T0FULL = 0;							// Write to Timer full event flag to reset it

	for (i = 0; i < 8; i++)
	{
		Character >>= 1;				// Shift Receiver byte one bit right
		if (P1IN & (GPR0 & 0x0F))
			Character |= 0x80;			// Set lowest bit if high level on RX line
		IDLE = 1;						// Wait for a timer event before starting reseption
		T0FULL = 0;						// Write to Timer full event flag to reset it
	}

	// RESTORE old Timer SFR values
	TMOD = TMOD_old;
	TH0 = TH0_old;
	TL0 = TL0_old;

	return Character;
}
 
/**********************************************************************************
 This function configures the RF Transmitter SFR RFTX
 according to the defines in SP35_Defs.h. It returns the configured data
**********************************************************************************/
char RF_Config(void)
{
	char temp=0x00;
	
	#ifdef _18080000_Crystal_433_92MHz
		temp |= 0x04;
	#endif
	#ifdef _2PA_Stages
		temp |= 0x01;
	#endif
	#ifdef _INV
		temp |= 0x40;
	#endif
	#ifdef _50_DC
		temp |= 0x10;
	#endif
	#ifdef _ASK
		temp |= 0x20;
	#endif
	RFTX = temp;
	return temp;
}	

