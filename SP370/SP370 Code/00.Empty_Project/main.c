/* ****************************************************************************************************/
/*                                          Program for SP37		                                  */
/*   -----------------------------------------------------------------------------------------------  */
/*                                                                                                    */
/*   Purpose: 	 	                                                            
/*				                                                                                      */
/*   Filename:   	main.c                                                                            */
/*                                                                                                    */
/*   Target:     	SP37                                                                              */
/*                                                                                                    */
/*   Dev. Envir: 	                                                                				  */
/*               	  																				  */
/*   Author:     		                                                 	   		              	  */
/*                                                                     	                              */
/*   History:    											  		  								  */
/*				 					                                                                  */
/*               	  																				  */
/*					                                                                                  */
/*                                                                                                    */
/*   Status:                                                                                          */
/* ************************************************************************************************** */
/*  (C)opyright Infineon Technologies AG. All rights reserved.                                        */
/* ****************************************************************************************************/
/*  This SOFTWARE is Provided "AS IS" Without ANY WARRANTIES OF ANY KIND, WHETHER
/*  EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
/*  MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE or warranties of
/*  non-infringement of THIRD PARTY intellectual property rights. infineon
/*  disclaims all liability regardless of the cause in law, in particular, but
/*  not limited to, the liability for indirect or consequential damages arising
/*  from interrupted operation, loss of profits, loss of information and data,
/*  unless in cases of gross negligence, intent, lack of assured characteristics
/*  or in any cases where liability is mandatory at law.
/* ****************************************************************************************************/

/**********************************************************************************
 Includes
***********************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include "SP37_DevLib.h"


/**********************************************************************************
 Defines
***********************************************************************************/

/**********************************************************************************
 Function Prototypes
***********************************************************************************/


/**********************************************************************************
 Global Variables
***********************************************************************************/


/**********************************************************************************
 functions
***********************************************************************************/

/**********************************************************************************
 Main Routine, executed @ every Wakeup or System- Reset
**********************************************************************************/
void main(void)
{
	P1DIR = 0x00;
	P1OUT &= ~((1<<0) | (1<<1));

	P1SENS &= ~0xFF;
	while(1);	
}




