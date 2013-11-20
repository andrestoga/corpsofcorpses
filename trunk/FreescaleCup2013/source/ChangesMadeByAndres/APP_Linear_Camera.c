/*============================================================================*/
/*                        Tortoise Team			                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %APP_Linear_Camera.c%
* Instance:         RPL_1
* %version:         1.2 %
* %created_by:      Andres Torres Garcia %
* %date_created:    Sunday Sep  30 14:38:03 2012 %
*=============================================================================*/
/* DESCRIPTION : C source file for the application layer of the Linear Camera */
/*============================================================================*/
/* FUNCTION COMMENT : This file contains the declarations and definitions of  */
/*					  the variables, and functions of the application layer of*/													  
/*					  the camera.											  */ 
/*					  	  											  		  */
/* 					                      									  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 30/09/2012  |                               | Andres Torres    */
/*  1.1      | 04/10/2012  |                               | Andres Torres    */
/*  1.2      | 07/10/2012  |                               | Andres Torres    */
/*  1.3      | 13/11/2012  |                               | Andres Torres    */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "TFC\TFC.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*!
  \def GOAL
  Pattern for a goal.
*/
#define GOAL				42		//0010-1010 - 7 shifts
/*!
  \def GOAL_2
  Pattern for a goal.
*/
#define GOAL_2				21		//0001-0101 - 5 shifts
/*!
  \def BLACK_LINE
  Pattern for a black line.
*/
#define BLACK_LINE	 		2		//0000-0010 - 3 shifts
/*!
  \def PIN_DEBUG
  PIN for debug.
*/
#define PIN_DEBUG			1
/*!
  \def CHAR_BIT
  Useful for the function getAbs
*/
#define CHAR_BIT 			8

/* LONG and STRUCTURE constants */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 

/** \brief Tolerance range for the width of the line */
const int8_t sb_RANGE = 4;

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/

/** \brief Left corner of the black line */
uint8_t ub_Left_Corner = 0;

uint8_t ub_Left_Corner2 = 0;

/** \brief Right corner of the black line */
uint8_t ub_Right_Corner = 0;

uint8_t ub_Right_Corner2 = 0;

/** \brief Width of the black line */
uint8_t ub_Black_Strip_Width = 0;

uint8_t ub_Black_Strip_Width2 = 0;

/** \brief The center of the black line */
uint8_t ub_Black_Strip_Center = 0;

uint8_t ub_Black_Strip_Center2 = 0;

/** \brief Flat that determines if we found a goal. */
uint8_t ub_IsGoal = 0;

uint8_t ub_IsGoal2 = 0;

/** \brief Flag that determines the time to proccess the pixels of the linear camera. */
uint8_t ub_Can_Process_Pixels = 0;

/** \brief Pixels of the camera binarize */
uint8_t ub_Bin_Pixels[NUM_PIXELS];

/** \brief Array of line centers. */
uint8_t ub_Line_Average[CAMERA_AVG];

uint8_t ub_Line_Average2[CAMERA_AVG];

extern volatile uint16_t  *LineScanImage0;

/** \brief The threshold that helps us to binarize the pixels. */
int16_t sw_Threshold = 2250;

/** \brief Holds important information about the pattern. */
Pattern_info pat_info;

Pattern_info pat_info2;

/** \brief Calibrate value of the width of the line. */
int8_t sb_BLACK_STRIP_WIDTH_MEASU = 0;

/** \brief Max pixel value */
static int16_t sw_max = 0;

/** \brief Min pix value */
static int16_t sw_min = 1023;

uint8_t width = 0;
uint8_t center = 0;

uint8_t width2 = 0;
uint8_t center2 = 0;

uint8_t FailCamLectCounter = 0;
uint8_t FailCamLectCounter2 = 0;

uint8_t SuccCamLecturesCounter = 0;
uint8_t SuccCamLecturesCounter2 = 0;

int16_t uw_CentralDifferentials [300];
int16_t uw_CentralDifferentials2 [300];

uint16_t ArrayOfLines [6];

uint8_t lineWidth = 0;
uint8_t lineCenter = 0;

uint8_t goalCounter = 0;

uint8_t GoalDetector = 0;
uint8_t GoalDetector2 = 0;

uint8_t IsGoalDetected = 0;
uint8_t IsGoalDetected2 = 0;

int8_t sb_BLACK_STRIP_WIDTH_MEASU2 = 0;
uint16_t ArrayOfLines2 [6];

uint8_t lineWidth2 = 0;
uint8_t lineCenter2 = 0;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

/* Private functions prototypes */
/* ---------------------------- */
void vfn_saveLineCenterPosition(void);
void vfn_saveLineCenterPosition2(void);
void vfn_binarize(void);
void vfn_binarize2(void);
void vfn_detectLine(void);
void vfn_detectLine2(void);
void vfn_processPixels(void);
void vfn_calibrateThreshold(void);
void vfn_calibrateLine(void);
void vfn_isValidLine(uint8_t width, uint8_t center, uint8_t left, uint8_t right);
void vfn_isValidLine2(uint8_t width, uint8_t center, uint8_t left, uint8_t right);

void CalculateCentralDifferentials(int max);
uint8_t Get_Lowest_Highest_Values(uint8_t max);
void vfn_ProcessPixels_V2();
uint8_t FoundLastGreater(uint8_t firstGreater, uint8_t max);
uint8_t Identify(uint8_t max);

void CalculateCentralDifferentials2(int max);
uint8_t FoundLastGreater2(uint8_t firstGreater, uint8_t max);
uint8_t Get_Lowest_Highest_Values2(uint8_t max);
uint8_t Identify2(uint8_t max);

/* Exported functions prototypes */
/* ----------------------------- */
//void vfnCalibrateLinearCamera(void);
uint8_t ub_PowerOfTwo( uint8_t ub_x );
uint16_t getAbs(int16_t num);
uint8_t CollisionAvoider();

/* Inline functions */
/* ---------------- */

/* Private functions */
/* ----------------- */

uint8_t FoundLastGreater2(uint8_t firstGreater, uint8_t max)
{
	uint8_t lastGreater = firstGreater;

	do
	{
		lastGreater++;

	} while (uw_CentralDifferentials2[lastGreater] > 300 && lastGreater < max);

	lastGreater--;

	return lastGreater;
}

uint8_t Identify(uint8_t max)
{
	uint16_t i;
	uint8_t k;

	uint8_t toggleNegPos = 1;
	uint8_t lineCounter = 0;

	int16_t tmpLeft = -1;
	int16_t tmpRight = -1;

	uint8_t inPos = 0;
	uint8_t countTrans = 0;

	for (i = 0, k = 0; i < max; i++)
	{
		if (uw_CentralDifferentials[i] > 0)
		{
			inPos = 1;

			if (uw_CentralDifferentials[i] >= 300 && toggleNegPos == 0)
			{
				toggleNegPos = 1;

				tmpRight = FoundLastGreater(i, max);
				
				ArrayOfLines[k] = tmpLeft;
				ArrayOfLines[k + 1] = tmpRight;
				k += 2;
				lineCounter++;

				tmpLeft = tmpRight = -1;

				countTrans = 0;
			}
		}
		else if (uw_CentralDifferentials[i] != 0)
		{
			if (tmpLeft != -1 && inPos)
			{
				countTrans++;

				if (uw_CentralDifferentials[i + 1] < 0 && countTrans > 2)
				{
					toggleNegPos = 1;
					tmpLeft = -1;

					countTrans = 0;
				}
			}

			inPos = 0;

			if (uw_CentralDifferentials[i] <= -300 && toggleNegPos == 1)
			{
				toggleNegPos = 0;

				tmpLeft = i;
			}
		}
	}

	//Calculate the width  and the center of the line
	switch (lineCounter)
	{
		//It's a black line
		case 1:

			lineWidth = ArrayOfLines[1] - ArrayOfLines[0];
			lineCenter = ArrayOfLines[0] + (lineWidth / 2);

			return 1;

		//It's not a valid line
		default:

			return 0;
	}
}

uint8_t Identify2(uint8_t max)
{
	uint16_t i;
	uint8_t k;

	uint8_t toggleNegPos = 1;
	uint8_t lineCounter = 0;

	int16_t tmpLeft = -1;
	int16_t tmpRight = -1;

	uint8_t inPos = 0;
	uint8_t countTrans = 0;

	for (i = 0, k = 0; i < max; i++)
	{
		if (uw_CentralDifferentials2[i] > 0)
		{
			inPos = 1;

			if (uw_CentralDifferentials2[i] >= 300 && toggleNegPos == 0)
			{
				toggleNegPos = 1;

				tmpRight = FoundLastGreater2(i, max);
				
				ArrayOfLines2[k] = tmpLeft;
				ArrayOfLines2[k + 1] = tmpRight;
				k += 2;
				lineCounter++;

				tmpLeft = tmpRight = -1;

				countTrans = 0;
			}
		}
		else if (uw_CentralDifferentials2[i] != 0)
		{
			if (tmpLeft != -1 && inPos)
			{
				countTrans++;

				if (uw_CentralDifferentials2[i + 1] < 0 && countTrans > 2)
				{
					toggleNegPos = 1;
					tmpLeft = -1;

					countTrans = 0;
				}
			}

			inPos = 0;

			if (uw_CentralDifferentials2[i] <= -300 && toggleNegPos == 1)
			{
				toggleNegPos = 0;

				tmpLeft = i;
			}
		}
	}

	//Calculate the width  and the center of the line
	switch (lineCounter)
	{
		//It's a black line
		case 1:

			lineWidth2 = ArrayOfLines2[1] - ArrayOfLines2[0];
			lineCenter2 = ArrayOfLines2[0] + (lineWidth2 / 2);

			return 1;

		//It's not a valid line
		default:

			return 0;
	}
}

uint8_t FoundLastGreater(uint8_t firstGreater, uint8_t max)
{
	uint8_t lastGreater = firstGreater;

	do
	{
		lastGreater++;

	} while (uw_CentralDifferentials[lastGreater] > 300 && lastGreater < max);

	lastGreater--;

	return lastGreater;
}

void vfn_ProcessPixels_V2()
{
	CalculateCentralDifferentials(NUM_PIXELS);
	CalculateCentralDifferentials2(NUM_PIXELS);
	
	//TODO: Make it generic
	vfn_saveLineCenterPosition();
	vfn_saveLineCenterPosition2();
	
	switch (Get_Lowest_Highest_Values(NUM_PIXELS))
	{
		case 1:
			
			ub_Black_Strip_Width = lineWidth;
			ub_Line_Average[0] = ub_Black_Strip_Center = lineCenter;
			
			if (GoalDetector == 3)
			{
				TFC_BAT_LED0_ON;
				
				//IsGoalDetected = 1;
			}
			
//			if (IsGoalDetected == 1 && GoalDetector != 3)
//			{
//				TFC_BAT_LED0_TOGGLE;
//				IsGoalDetected = 0;
//			}
			
			break;
			
//		case 2:
//			
//			ub_Black_Strip_Width = lineWidth;
//			ub_Line_Average[0] = ub_Black_Strip_Center = lineCenter;
//			
//		/* 	goalCounter++;
//			
//			if (goalCounter >= 2) {
//				//Stop Motors!!!
//			} */
//			
//			TFC_BAT_LED0_ON;
//			
//			break;
			
		default:
			
			break;
	}
	
	switch (Get_Lowest_Highest_Values2(NUM_PIXELS))
	{
			case 1:
				
				ub_Black_Strip_Width2 = lineWidth2;
				ub_Line_Average2[0] = ub_Black_Strip_Center2 = lineCenter2;
				
				if (GoalDetector2 == 3)
				{
					TFC_BAT_LED1_ON;
					
					//IsGoalDetected2 = 1;
				}
				
	//			if (IsGoalDetected2 == 1 && GoalDetector2 != 3)
	//			{
	//				TFC_BAT_LED1_TOGGLE;
	//				IsGoalDetected2 = 0;
	//			}
				
				break;
				
	//		case 2:
	//			
	//			ub_Black_Strip_Width = lineWidth;
	//			ub_Line_Average[0] = ub_Black_Strip_Center = lineCenter;
	//			
	//		/* 	goalCounter++;
	//			
	//			if (goalCounter >= 2) {
	//				//Stop Motors!!!
	//			} */
	//			
	//			TFC_BAT_LED0_ON;
	//			
	//			break;
				
			default:
				
				break;
		}
}

/**************************************************************
 *  Name                 : 	vfn_saveLineCenterPosition
 *  Description          :	Store different reads of the line center in an array.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Store different reads of the line center in an array.
/////////////////////////////////////////////////////////////////////////

void CalculateCentralDifferentials(int max)
{
	int i;

	uw_CentralDifferentials[0] = (LineScanImage0[1] - LineScanImage0[0]) / 2;
	uw_CentralDifferentials[max - 1] = (LineScanImage0[max - 1] - LineScanImage0[max - 2]) / 2;

	for (i = 1; i < max - 1; i++)
	{
		uw_CentralDifferentials[i] = (LineScanImage0[i + 1] - LineScanImage0[i - 1]) / 2;
	}
}

void CalculateCentralDifferentials2(int max)
{
	int i;

	uw_CentralDifferentials2[0] = (LineScanImage1[1] - LineScanImage1[0]) / 2;
	uw_CentralDifferentials2[max - 1] = (LineScanImage1[max - 1] - LineScanImage1[max - 2]) / 2;

	for (i = 1; i < max - 1; i++)
	{
		uw_CentralDifferentials2[i] = (LineScanImage1[i + 1] - LineScanImage1[i - 1]) / 2;
	}
}

uint8_t Get_Lowest_Highest_Values2(uint8_t max)
{
	uint16_t i;
	uint8_t k;

	uint8_t toggleNegPos = 1;
	uint8_t lineCounter = 0;

	int16_t tmpLeft = -1;
	int16_t tmpRight = -1;

	uint8_t inPos = 0;
	uint8_t countTrans = 0;
	
	GoalDetector2 = 0;

	for (i = 0, k = 0; i < max; i++)
	{
		if (uw_CentralDifferentials2[i] > 0)
		{
			inPos = 1;

			if (uw_CentralDifferentials2[i] >= 300 && toggleNegPos == 0)
			{
				toggleNegPos = 1;

				tmpRight = FoundLastGreater2(i, max);
				
				GoalDetector2++;

				
				if( ( ( sb_BLACK_STRIP_WIDTH_MEASU2 - sb_RANGE ) <= ( tmpRight - tmpLeft ) ) && ( ( sb_BLACK_STRIP_WIDTH_MEASU2 + sb_RANGE ) >= ( tmpRight - tmpLeft ) ) )
				//if ((tmpRight - tmpLeft) > 3)
				{
					ArrayOfLines2[k] = tmpLeft;
					ArrayOfLines2[k + 1] = tmpRight;
					k += 2;
					lineCounter++;

					tmpLeft = tmpRight = -1;

					countTrans = 0;
				}
			}
		}
		else if (uw_CentralDifferentials2[i] != 0)
		{
			if (tmpLeft != -1 && inPos)
			{
				countTrans++;

				if (uw_CentralDifferentials2[i + 1] < 0 && countTrans > 2)
				{
					toggleNegPos = 1;
					tmpLeft = -1;

					countTrans = 0;
				}
			}

			inPos = 0;

			if (uw_CentralDifferentials2[i] <= -300 && toggleNegPos == 1)
			{
				toggleNegPos = 0;

				tmpLeft = i;
			}
		}
	}

	//Calculate the width  and the center of the line
	switch (lineCounter)
	{
		//It's a black line
		case 1:

			lineWidth2 = ArrayOfLines2[1] - ArrayOfLines2[0];
			lineCenter2 = ArrayOfLines2[0] + (lineWidth2 / 2);
			
			SuccCamLecturesCounter2++;

			return 1;

		//It's a goal
		case 3:

			lineWidth2 = ArrayOfLines2[3] - ArrayOfLines2[2];
			lineCenter2 = ArrayOfLines2[2] + (lineWidth2 / 2);
			
			SuccCamLecturesCounter2++;

			//Stop the car!!!

			return 2;

		//It's not a valid line
		default:
			
			FailCamLectCounter2++;

			return 0;
	}
}

uint8_t Get_Lowest_Highest_Values(uint8_t max)
{
	uint16_t i;
	uint8_t k;

	uint8_t toggleNegPos = 1;
	uint8_t lineCounter = 0;

	int16_t tmpLeft = -1;
	int16_t tmpRight = -1;

	uint8_t inPos = 0;
	uint8_t countTrans = 0;
	
	GoalDetector = 0;

	for (i = 0, k = 0; i < max; i++)
	{
		if (uw_CentralDifferentials[i] > 0)
		{
			inPos = 1;

			if (uw_CentralDifferentials[i] >= 300 && toggleNegPos == 0)
			{
				toggleNegPos = 1;

				tmpRight = FoundLastGreater(i, max);
				
				GoalDetector++;

				if( ( ( sb_BLACK_STRIP_WIDTH_MEASU - sb_RANGE ) <= ( tmpRight - tmpLeft ) ) && ( ( sb_BLACK_STRIP_WIDTH_MEASU + sb_RANGE ) >= ( tmpRight - tmpLeft ) ) )
				//if ((tmpRight - tmpLeft) > 3)
				{
					ArrayOfLines[k] = tmpLeft;
					ArrayOfLines[k + 1] = tmpRight;
					k += 2;
					lineCounter++;

					tmpLeft = tmpRight = -1;

					countTrans = 0;
				}
			}
		}
		else if (uw_CentralDifferentials[i] != 0)
		{
			if (tmpLeft != -1 && inPos)
			{
				countTrans++;

				if (uw_CentralDifferentials[i + 1] < 0 && countTrans > 2)
				{
					toggleNegPos = 1;
					tmpLeft = -1;

					countTrans = 0;
				}
			}

			inPos = 0;

			if (uw_CentralDifferentials[i] <= -300 && toggleNegPos == 1)
			{
				toggleNegPos = 0;

				tmpLeft = i;
			}
		}
	}

	//Calculate the width  and the center of the line
	switch (lineCounter)
	{
		//It's a black line
		case 1:

			lineWidth = ArrayOfLines[1] - ArrayOfLines[0];
			lineCenter = ArrayOfLines[0] + (lineWidth / 2);
			
			SuccCamLecturesCounter++;

			return 1;

		//It's a goal
		case 3:

			lineWidth = ArrayOfLines[3] - ArrayOfLines[2];
			lineCenter = ArrayOfLines[2] + (lineWidth / 2);
			
			SuccCamLecturesCounter++;

			//Stop the car!!!

			return 2;

		//It's not a valid line
		default:
			
			FailCamLectCounter++;

			return 0;
	}
}

 void vfn_saveLineCenterPosition(void)
 {
	 uint8_t i;

	for(i = CAMERA_AVG; i > 0; i--)
	{
		ub_Line_Average[i] = ub_Line_Average[i-1];
	}	
 }
 
 void vfn_saveLineCenterPosition2(void)
 {
	 uint8_t i;

	for(i = CAMERA_AVG; i > 0; i--)
	{
		ub_Line_Average2[i] = ub_Line_Average2[i-1];
	}	
 }
 
 void vfn_detectLine2(void)
 {
	width2 = 0;
	center2 = 0;

	//Shifting to the right the array of line centers.
	vfn_saveLineCenterPosition2();
	
	ub_IsGoal2 = 0;
	
	//Is it a goal?
	if( pat_info2.value ==  GOAL && pat_info2.valid == 7)
	{
		width2 = pat_info2.width[3] - pat_info2.width[2];
		center2 = width2 / 2 + pat_info2.width[2];
		ub_IsGoal2 = 1;
		
		vfn_isValidLine2( width2, center2, pat_info2.width[2], pat_info2.width[3] - 1);
	}//Is a line?
	else if( pat_info2.value ==  BLACK_LINE && pat_info2.valid == 3 )
	{
		width2 = pat_info2.width[1] - pat_info2.width[0];
		center2 = width2 / 2 + pat_info2.width[0];
		
		vfn_isValidLine2( width2, center2, pat_info2.width[0], pat_info2.width[1] - 1);
	}//Is a goal?
	else if( pat_info2.value ==  GOAL_2 && pat_info2.valid == 5 )
	{
		width2 = pat_info2.width[2] - pat_info2.width[1];
		center2 = width2 / 2 + pat_info2.width[1];
		ub_IsGoal2 = 1;
		
		vfn_isValidLine2( width2, center2, pat_info2.width[1], pat_info2.width[2] - 1);
	}
 }
 
 /**************************************************************
 *  Name                 : 	vfn_detectLine
 *  Description          :	Try to detect the line or the goal.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Try to detect the line or the goal.
/////////////////////////////////////////////////////////////////////////
void vfn_detectLine(void)
{
	width = 0;
	center = 0;

	//Shifting to the right the array of line centers.
	vfn_saveLineCenterPosition();
	
	ub_IsGoal = 0;
	
	//Is it a goal?
	if( pat_info.value ==  GOAL && pat_info.valid == 7)
	{
		width = pat_info.width[3] - pat_info.width[2];
		center = width / 2 + pat_info.width[2];
		ub_IsGoal = 1;
		
		vfn_isValidLine( width, center, pat_info.width[2], pat_info.width[3] - 1);
	}//Is a line?
	else if( pat_info.value ==  BLACK_LINE && pat_info.valid == 3 )
	{
		width = pat_info.width[1] - pat_info.width[0];
		center = width / 2 + pat_info.width[0];
		
		vfn_isValidLine( width, center, pat_info.width[0], pat_info.width[1] - 1);
	}//Is a goal?
	else if( pat_info.value ==  GOAL_2 && pat_info.valid == 5 )
	{
		width = pat_info.width[2] - pat_info.width[1];
		center = width / 2 + pat_info.width[1];
		ub_IsGoal = 1;
		
		vfn_isValidLine( width, center, pat_info.width[1], pat_info.width[2] - 1);
	}
	else
	{
		FailCamLectCounter++;
	}
}

 /**************************************************************
 *  Name                 : 	vfn_isValidLine
 *  Description          :	Check if the line is a valid one and if it is, assign values.
 *  Parameters           :  [Input: ub_width, ub_center, ub_left ,ub_right, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Check if the line is a valid one and if it is, assign values.
/// \param ub_width width of the line.
/// \param ub_center center of the line.
/// \param ub_left left corner of the line.
/// \param ub_right right corner of the line.
/////////////////////////////////////////////////////////////////////////
void vfn_isValidLine(uint8_t ub_width, uint8_t ub_center, uint8_t ub_left, uint8_t ub_right)
{
	if( ( ( sb_BLACK_STRIP_WIDTH_MEASU - sb_RANGE ) <= ub_width ) && ( ( sb_BLACK_STRIP_WIDTH_MEASU + sb_RANGE ) >= ub_width ) )
	{
		ub_Black_Strip_Width = ub_width;
		
		ub_Line_Average[0] = ub_Black_Strip_Center = ub_center;
		
		ub_Left_Corner = ub_left;
		ub_Right_Corner = ub_right;
		
		SuccCamLecturesCounter++;
	}
	else
	{
		ub_IsGoal = 0;
	}
}

void vfn_isValidLine2(uint8_t ub_width, uint8_t ub_center, uint8_t ub_left, uint8_t ub_right)
{
	if( ( ( sb_BLACK_STRIP_WIDTH_MEASU - sb_RANGE ) <= ub_width ) && ( ( sb_BLACK_STRIP_WIDTH_MEASU + sb_RANGE ) >= ub_width ) )
	{
		ub_Black_Strip_Width2 = ub_width;
		
		ub_Line_Average2[0] = ub_Black_Strip_Center2 = ub_center;
		
		ub_Left_Corner2 = ub_left;
		ub_Right_Corner2 = ub_right;
	}
	else
	{
		ub_IsGoal2 = 0;
	}
}

/**************************************************************
 *  Name                 : 	vfnProcess_Pixels
 *  Description          :	Process the pixels of the linear camera and detect the line
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Process the pixels of the linear camera and detect the line
/////////////////////////////////////////////////////////////////////////
void vfn_processPixels(void)
{	
	vfn_binarize();
	vfn_detectLine();
	
	vfn_binarize2();
	vfn_detectLine2();
}

void vfn_binarize2(void)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t width = 0;
	
	pat_info2.value = 0;
	pat_info2.valid = 0;
	pat_info2.width[j] = 0;
	
	uint8_t ub_currValue = 2;
	
	for( i = 0; i < NUM_PIXELS; i++)
	{	
		width++;
		
		if( LineScanImage1[i] > sw_Threshold && ub_currValue != 0 )
		{
			if( ub_currValue != 2 )
			{
				pat_info2.width[j] = width - 1;
				j++;
			}
			
			pat_info2.valid++;
			pat_info2.value = pat_info2.value << 1;
			
			ub_currValue = 0;
		}
		else if( LineScanImage1[i] < sw_Threshold && ub_currValue != 1 )
		{
			if( ub_currValue != 2 )
			{
				pat_info2.width[j] = width - 1;
				j++;
			}
			
			pat_info2.valid++;
			pat_info2.value = pat_info2.value << 1;
			pat_info2.value |= 1;
			
			ub_currValue = 1;
		}
	}
	
	pat_info2.width[j] = width;
}

/**************************************************************
 *  Name                 : 	vfn_binarize
 *  Description          :	Create a pattern from the pixels.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Create a pattern from the pixels.
/////////////////////////////////////////////////////////////////////////
void vfn_binarize()
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t width = 0;
	
	pat_info.value = 0;
	pat_info.valid = 0;
	pat_info.width[j] = 0;
	
	uint8_t ub_currValue = 2;
	
	for( i = 0; i < NUM_PIXELS; i++)
	{	
		width++;
		
		if( LineScanImage0[i] > sw_Threshold && ub_currValue != 0 )
		{
			if( ub_currValue != 2 )
			{
				pat_info.width[j] = width - 1;
				j++;
			}
			
			pat_info.valid++;
			pat_info.value = pat_info.value << 1;
			
			ub_currValue = 0;
		}
		else if( LineScanImage0[i] < sw_Threshold && ub_currValue != 1 )
		{
			if( ub_currValue != 2 )
			{
				pat_info.width[j] = width - 1;
				j++;
			}
			
			pat_info.valid++;
			pat_info.value = pat_info.value << 1;
			pat_info.value |= 1;
			
			ub_currValue = 1;
		}
		
		/*if(LineScanImage0[i] > sw_Threshold)
		{
			ub_Bin_Pixels[i] = 0;
		}
		else
		{
			ub_Bin_Pixels[i] = 1;
		}*/
	}
	
	pat_info.width[j] = width;
}

/**************************************************************
 *  Name                 : 	vfn_calibrateLine
 *  Description          :	Measure the line in pixels
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Measure the line in pixels
/////////////////////////////////////////////////////////////////////////
void vfn_calibrateLine(void)
{
	//Create the pattern.
//	vfn_binarize();
//	
//	//Is a black line?
//	if( pat_info.value ==  BLACK_LINE && pat_info.valid == 3 )
//	{
//		ub_Left_Corner = pat_info.width[0];
//		ub_Right_Corner = pat_info.width[1] - 1;
//	
//		sb_BLACK_STRIP_WIDTH_MEASU = ub_Black_Strip_Width = pat_info.width[1] - pat_info.width[0];
//		ub_Black_Strip_Center = ub_Black_Strip_Width / 2 + pat_info.width[0];
//	}
	
	CalculateCentralDifferentials(NUM_PIXELS);
	CalculateCentralDifferentials2(NUM_PIXELS);
		
	switch (Identify(NUM_PIXELS)) {
	
		case 1:
			
			sb_BLACK_STRIP_WIDTH_MEASU = ub_Black_Strip_Width = lineWidth;
			ub_Line_Average[0] = ub_Black_Strip_Center = lineCenter;
			
			//TERMINAL_PRINTF( "%d\r\n",1 );
			
			break;
			
		default:
			break;
	}
	
	switch (Identify2(NUM_PIXELS)) {
		
			case 1:
				
				sb_BLACK_STRIP_WIDTH_MEASU2 = ub_Black_Strip_Width2 = lineWidth2;
				ub_Line_Average2[0] = ub_Black_Strip_Center2 = lineCenter2;
				
				//TERMINAL_PRINTF( "%d\r\n",1 );
				
				break;
				
			default:
				break;
		}
}

/**************************************************************
 *  Name                 : 	vfn_calibrateThreshold
 *  Description          :	Calculate the threshold automatically
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Calculate the threshold automatically
/////////////////////////////////////////////////////////////////////////
void vfn_calibrateThreshold(void)
{
	int16_t sw_tmp = 0;
	
	uint8_t i;
	
	sw_max = 0;
	sw_min = 1023;
	
	for( i = 0; i < NUM_PIXELS; i++)
	{
		if( LineScanImage0[i]  > sw_max )
		{
			sw_max = LineScanImage0[i];
		}
		
		if( LineScanImage0[i]  < sw_min )
		{
			sw_min = LineScanImage0[i];
		}
	}
	
	sw_tmp = sw_max - sw_min;
	
	sw_tmp = sw_tmp / 2;
	
	sw_Threshold = sw_tmp + sw_tmp / 2;
}

/* Exported functions */
/* ------------------ */

uint8_t CollisionAvoider()
{
//	if( SuccCamLecturesCounter == 200 )
//	{
//		SuccCamLecturesCounter = 0;
//		FailCamLectCounter = 0;
//	}
//	else if( FailCamLectCounter == 1 )
//	{
//		FailCamLectCounter = 0;
//		SuccCamLecturesCounter = 0;
//
//		return 0;
//	}
//
//	return 1;
	
	if( SuccCamLecturesCounter2 == 200 )
	{
		SuccCamLecturesCounter2 = 0;
		FailCamLectCounter2 = 0;
	}
	else if( FailCamLectCounter2 == 1 )
	{
		FailCamLectCounter2 = 0;
		SuccCamLecturesCounter2 = 0;

		return 0;
	}

	return 1;
}

/**************************************************************
 *  Name                 :	ub_PowerOfTwo
 *  Description          :	Elevates 2 to the power of x
 *  Parameters           :  [Input: ub_x, Output, Input / output]
 *  Return               :	T_UBYTE
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Elevates 2 to the power of x
/// \param ub_x power of x
/// \return result
/////////////////////////////////////////////////////////////////////////
uint8_t ub_PowerOfTwo( uint8_t ub_x )
{
	uint8_t ub_y = 1;
	
	ub_x--;

	while( ub_x )
	{
		ub_y = ub_y << 1;
		ub_x--;
	}
	
	return ub_y;
}


/**************************************************************
 *  Name                 :	getAbs
 *  Description          :	Gets the absolute value of num.
 *  Parameters           :  [Input: sw_num, Output, Input / output]
 *  Return               :	uint16_t
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Gets the absolute value of num.
/// \param sw_num the number that you want to get its absolut.
/// \return the absolute number of sw_num
/////////////////////////////////////////////////////////////////////////
uint16_t getAbs(int16_t sw_num)
{
	int16_t const sw_mask = sw_num >> (sizeof(int16_t) * CHAR_BIT - 1);
  	return ((sw_num ^ sw_mask) - sw_mask);
}

/**************************************************************
 *  Name                 :	vfnCalibrateLinearCamera
 *  Description          :	Calibrate the Linear Camera.
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    No
 **************************************************************/
///////////////////////////////////////////////////////////////////////
/// \brief Calibrate the Linear Camera.
/////////////////////////////////////////////////////////////////////////
/*void vfnCalibrateLinearCamera(void)
{
	static uint8_t ub_calibrationState = 0;
	
	switch(ub_calibrationState)
	{
		case 0:					
				if(Check_Btn_Press(BTN_3))
				{
					ub_calibrationState = 1;
					
					APPLeds_Led4_app();
				}
				else
				{
					vfn_calibrateThreshold();
				}
				
		break;
		
		case 1:
				if(Check_Btn_Press(BTN_3))
				{
					ub_calibrationState = 2;
					
					APPLeds_Led4_app();
				}
				else
				{
					vfn_calibrateLine();
				}
				
		break;
		
		case 2:
		
				//Do nothing
		
		break;
		
	}
}*/
