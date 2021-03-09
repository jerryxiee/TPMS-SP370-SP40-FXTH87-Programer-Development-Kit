/* ****************************************************************************************************/
/*                             Development Library Functions for SP37 Application Development         */
/*   -----------------------------------------------------------------------------------------------  */
/*                                                                                                    */   
/*   Purpose: 	 Software UART, Automatic Register Configurations,...								  */
/*                                                                                                    */
/*                                                                                                    */
/*   Filename:   SP37_DevLib.h                                                                        */
/*                                                                                                    */
/*   Target:     SP37                                                                                 */
/*                                                                                                    */
/*   Dev. Envir: Keil Software C51 V7.10                                                              */
/*               µVision2 V2.40                                                                       */
/*   Author:     TL		                                                 	   		                  */
/*                                                                     	                              */
/*   History:    30.July 2008: First Release				                                          */
/*				 																					  */				 
/*                                                                                                    */
/*   Status:     Release V1.0                                                                         */
/* ************************************************************************************************** */
/*  (C)opyright Infineon Technologies AG. All rights reserved.                                        */
/* ****************************************************************************************************/

/*********************************************************************************************
 Define used crystal. This is needed for the STARTUP.A51 and for "RF_Config()"  
**********************************************************************************************/
//#define _19687500_Crystal_315MHz
#define _18080000_Crystal_433_92MHz

/**********************************************************************************
 RF Settings - these have only impact if "RF_Config()" is called by 
 			   the application. Otherwise the settings here show no effect 
***********************************************************************************/
#define _1PA_Stage
//#define _2PA_Stages

//#define _FSK
#define _ASK

#define _NOT_INV
//#define _INV

#define _30_DC
//#define _50_DC

/**********************************************************************************
 Peripheral abbrevations 
***********************************************************************************/
#define PP0 							(1<<0)			   
#define PP1 							(1<<1)
#define PP2								(1<<2)

/**********************************************************************************
 Function Prototypes
***********************************************************************************/
#ifdef __C51__
	extern void RS232_Init(unsigned char Tx, Rx);
	extern void RS232_UnInit(unsigned char Tx, Rx);
	extern char putchar(char Result);
	extern char getchar(void);
	extern void RS232_Send_Hex (unsigned char Byte);
	extern void RS232_Send_Bin(char dat, char bits);
	extern void RC_Trimming(void);
	extern char RF_Config(void);	
#endif