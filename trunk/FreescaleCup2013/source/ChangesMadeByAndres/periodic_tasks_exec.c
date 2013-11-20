/*============================================================================*/
/*                     AZOR - EMBEDDED SYSTEMS SOFTWARE                       */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        periodic_tasks_exec.c
* version:         1.0 
* created_by:      MDRR
* date_created:    July 31 2013 
*=============================================================================*/
/* DESCRIPTION :  This file contains the periodic tasks definition.           */
/*============================================================================*/
/* FUNCTION COMMENT : Add here the user functionality, inside a periodic task */
/* according to the desired execution period.                                 */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 31/jul/2013 |                               | MDRR             */
/* This file is created based on apptask module from the old version of this  */
/* scheduler.                                                                 */
/*============================================================================*/

/* Includes */
/* -------- */
#include "periodic_tasks_exec.h"
#include "periodic_tasks_modules.h"


/**************************************************************
 *  Name                 : periodic_tasks_exec_5tks
 *	ID					 : TASK_5TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_5tks(void)
 {
	 //HAL_ControlSpeed();
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_10tks
 *	ID					 : TASK_10TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_10tks(void)
 {
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_20tks
 *	ID					 : TASK_20TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_20tks(void)
 {
//	 if(LineScanImageReady==1)
//	 {
//		 LineScanImageReady=0;
					
		(*ptrFctnMachineState[en_State])();
		
 		 //TERMINAL_PRINTF("\r\n");
// 		 TERMINAL_PRINTF("%d ", pat_info.value);
// 		 TERMINAL_PRINTF("%d ", pat_info.valid);
// 		 TERMINAL_PRINTF("%d ", ub_Black_Strip_Center);
// 		 TERMINAL_PRINTF("%d ", ub_Black_Strip_Width);
// 		 TERMINAL_PRINTF("\r\n");
 		 
// 		 for(i = 0;i < 128;i++)
// 		 {
// 			 //TERMINAL_PRINTF("%d",ub_Bin_Pixels[i]);
// 			 TERMINAL_PRINTF("%X ",LineScanImage0[i]);
// 		 }
// 		 
// 		 TERMINAL_PRINTF("\r\n");
		
//	 		TERMINAL_PRINTF("\r\n");
//	 		TERMINAL_PRINTF("L:");
//	 			
//	 		 for(i=0;i<128;i++)
//	 		 {
//	 			 TERMINAL_PRINTF("%X,",LineScanImage0[i]);
//	 		 }
//	 		
//	 		 for(i=0;i<128;i++)
//	 		 {
//	 			 TERMINAL_PRINTF("%X",LineScanImage1[i]);
//	 			 
//	 			 if(i==127)
//	 				 TERMINAL_PRINTF("\r\n",LineScanImage1[i]);
//	 			 else
//	 				 TERMINAL_PRINTF(",",LineScanImage1[i]);
//	 		}
 		 
 		 
 		 //Print speed
// 		 TERMINAL_PRINTF("%d", (uint8_t)(HAL_GetSpeed()*100));
// 		 TERMINAL_PRINTF("\r\n");
		 
	 	 //}
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_50tks
 *	ID					 : TASK_50TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_50tks(void)
 {
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_100tks
 *	ID					 : TASK_100TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_100tks(void)
 { 
	 

 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_500tks
 *	ID					 : TASK_500TKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_500tks(void)
 {
	 
 }
 
 /**************************************************************
 *  Name                 : periodic_tasks_exec_1Mtks
 *	ID					 : TASK_1MTKS
 *  Description          : Container for functionality that is 
                           executed periodically.
 *  Parameters           : none
 *  Return               : none
 *  Critical/explanation : no
 **************************************************************/
 void periodic_tasks_exec_1Mtks(void)
 {
	 //app_rgb_led_fsm();
 }
 
