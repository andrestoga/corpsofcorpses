/*============================================================================*/
/*                        Tortoise Team			                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %APP_Machine_State.c%
* Instance:         RPL_1
* %version:         1.0 %
* %created_by:      Andres Torres Garcia %
* %date_created:    Sunday Sep  30 14:38:03 2012 %
*=============================================================================*/
/* DESCRIPTION : C source file for the machine state.                         */
/*============================================================================*/
/* FUNCTION COMMENT : This file contains the function and variable definitions*/
/*					  of the machine state                                    */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 30/09/2012  |                               | Andres Torres    */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "TFC\TFC.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/

/** \brief Pointer to function for the machine state. */
void (*ptrFctnMachineState[NUM_STATES]) (void);

/** \brief State of the machine state. */
enum STATE en_State = FIRST_STATE;

/** \brief Variable used to toggle the state of the back wheels. */
static uint8_t toggle = 1;

uint32_t i = 0;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

/* Private functions prototypes */
/* ---------------------------- */

void vfnFirstState(void);
void vfnSecondState(void);
void vfnThirdState(void);
void vfnFourState(void);

/* Exported functions prototypes */
/* ----------------------------- */

void vfnInitStates(void);

/* Inline functions */
/* ---------------- */

/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : vfnFirstState
 *  Description          : The first state of the machine state.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief The first state of the machine state.
/////////////////////////////////////////////////////////////////////////
void vfnFirstState(void)
{
	//vfnCalibrate_FrontWheels();
	
	//Turn on led 1
	TFC_BAT_LED0_ON;

	if(TFC_PUSH_BUTTON_0_PRESSED)
	{
		en_State = SECOND_STATE;
		
		TFC_BAT_LED0_OFF;
		TFC_BAT_LED1_ON;
	}
}

/**************************************************************
 *  Name                 : vfnSecondState
 *  Description          :	The second state of the machine state.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief The second state of the machine state.
/////////////////////////////////////////////////////////////////////////
void vfnSecondState(void)
{
	if(TFC_PUSH_BUTTON_0_PRESSED)
	{
		en_State = THIRD_STATE;
	
		TFC_BAT_LED1_OFF;
		TFC_BAT_LED2_ON;
	}
	
	if(LineScanImageReady==1)
	 {
		LineScanImageReady=0;
		
		vfn_calibrateLine();
	 }
	
//	TERMINAL_PRINTF( "%d\r\n",ub_Black_Strip_Center );
//	TERMINAL_PRINTF( "%d\r\n",ub_Black_Strip_Width );
}

/**************************************************************
 *  Name                 : vfnThirdState
 *  Description          : The third state of the machine state.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief The third state of the machine state.
/////////////////////////////////////////////////////////////////////////
void vfnThirdState(void)
{
	if(TFC_PUSH_BUTTON_0_PRESSED)
	{
		en_State = FOUR_STATE;
		
		//vfnStart_DcMotor(2);
		
		TFC_BAT_LED2_OFF;
		TFC_BAT_LED3_ON;
	}
	
}

/**************************************************************
 *  Name                 : vfnFourState
 *  Description          : The four state of the machine state.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief The four state of the machine state.
/////////////////////////////////////////////////////////////////////////
void vfnFourState(void)
{
	float NewPwm;
	
//	if(TFC_PUSH_BUTTON_1_PRESSED)
//	{	
//		if(toggle)
//		{
//			toggle = 0;
//			//vfnStop_DcMotor(2);
//			TFC_HBRIDGE_DISABLE;
//		}
//		else
//		{
//			toggle = 1;
//			//vfnStart_DcMotor(2);
//			TFC_HBRIDGE_ENABLE;
//			//HAL_ResetPID_Values();		//Reset PID values
//		}
//	}
	
	//Toggle led 4
	TFC_BAT_LED3_TOGGLE;
	
	//Set a constant speed
	NewPwm = (MAL_ReadPot(0)+1)/2;
	HAL_SetMotorPWM(NewPwm,NewPwm);		//Without SPEED CONTROL
	//HAL_SetSpeed(NewPwm);				//With SPEED CONTROL
	
	
	if(LineScanImageReady==1)
	 {
		LineScanImageReady=0;
		
//		TERMINAL_PRINTF("\r\n");
//		TERMINAL_PRINTF("L:");
//			
//		 for(i=0;i<128;i++)
//		 {
//			 TERMINAL_PRINTF("%X,",LineScanImage0[i]);
//		 }
//		
//		 for(i=0;i<128;i++)
//		 {
//			 TERMINAL_PRINTF("%X",LineScanImage1[i]);
//			 
//			 if(i==127)
//				 TERMINAL_PRINTF("\r\n",LineScanImage1[i]);
//			 else
//				 TERMINAL_PRINTF(",",LineScanImage1[i]);
//		}
		
//		for(i = 0;i < 128;i++)
//		{
//			TERMINAL_PRINTF("%X",LineScanImage0[i]);
//			
//			 if(i != 127)
//				 TERMINAL_PRINTF(" ",LineScanImage0[i]);
//		}
//		
//		TERMINAL_PRINTF("\r\n");
		 
		//vfn_processPixels();
		
		vfn_ProcessPixels_V2();
	}
	
//	TERMINAL_PRINTF( "%d\r\n",ub_Black_Strip_Center );
//	TERMINAL_PRINTF( "%d\r\n",ub_Black_Strip_Width );
//	TERMINAL_PRINTF( "%d %d\r\n",sb_BLACK_STRIP_WIDTH_MEASU - sb_RANGE, sb_BLACK_STRIP_WIDTH_MEASU + sb_RANGE );
	
	if (CollisionAvoider()) {
		
		TFC_HBRIDGE_ENABLE;
		//HAL_ResetPID_Values();		//Reset PID values
		
	} else {
		TFC_HBRIDGE_DISABLE;
	}
	
	vfnFirstVersion();
	//vfnFuzzyAlgorithm();
	
//	vfnFirstOscar(MAL_ReadPot(0),MAL_ReadPot(1));
	
	//Testing
	//vfnSetPos_FrontWheels(SM_KNOB(GET_KNOB_VALUE));
}

/* Exported functions */
/* ------------------ */

/**************************************************************
 *  Name                 : vfnInitStates
 *  Description          : Initialize the pointer to function states.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Initialize the pointer to function states.
/////////////////////////////////////////////////////////////////////////
void vfnInitStates(void)
{
	ptrFctnMachineState[0] = &vfnFirstState;
	ptrFctnMachineState[1] = &vfnSecondState;
	ptrFctnMachineState[2] = &vfnThirdState;
	ptrFctnMachineState[3] = &vfnFourState;
}
