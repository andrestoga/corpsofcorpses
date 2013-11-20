/*============================================================================*/
/*                        Tortoise Team			                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %APP_Linear_Camera.h%
* Instance:         RPL_1
* %version:         1.3 %
* %created_by:      Andres Torres Garcia %
* %date_created:    Sunday Sep  30 14:38:03 2012 %
*=============================================================================*/
/* DESCRIPTION : Header file for the application layer of the linear camera   */
/*============================================================================*/
/* FUNCTION COMMENT : This file contains the declarations of the the variables*/
/*					  and functions of the application layer of the linear	  */
/*					  camera.								                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 30/09/2012  | SAR/SIF/SCN_xxx               | Andres Torres    */
/*  1.1      | 04/10/2012  |                               | Andres Torres    */
/*  1.2      | 07/10/2012  |                               | Andres Torres    */
/*  1.3      | 13/11/2012  |                               | Andres Torres    */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef APP_LINEAR_CAMERA_H                               /* To avoid double inclusion */
#define APP_LINEAR_CAMERA_H

/* Includes */
/* -------- */

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */
#include "TFC\TFC.h"
#include "TFC\HAL_Linear_Camera.h"

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */

extern uint8_t ub_PowerOfTwo( uint8_t ub_x );
extern uint16_t getAbs(int16_t num);
extern void vfn_processPixels(void);
extern void vfn_calibrateLine(void);
extern uint8_t CollisionAvoider();

extern void vfn_ProcessPixels_V2();

/* Functions macros */

/* Exported defines */

/*!
  \def CAMERA_AVG
  Number of line centers to store.
*/
#define CAMERA_AVG	6

/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */

extern uint8_t ub_Left_Corner;
extern uint8_t ub_Right_Corner;
extern uint8_t ub_Black_Strip_Width;
extern uint8_t ub_Black_Strip_Center;
extern uint8_t ub_IsGoal;
extern uint8_t ub_Can_Process_Pixels;

extern uint8_t ub_Left_Corner2;
extern uint8_t ub_Right_Corner2;
extern uint8_t ub_Black_Strip_Width2;
extern uint8_t ub_Black_Strip_Center2;
extern uint8_t ub_IsGoal2;

extern uint8_t ub_Bin_Pixels[NUM_PIXELS];

extern uint8_t ub_Line_Average[CAMERA_AVG];
extern uint8_t ub_Line_Average2[CAMERA_AVG];

extern int8_t sb_BLACK_STRIP_WIDTH_MEASU;
extern const int8_t sb_RANGE;

/* WORD constants */

extern int16_t sw_Threshold;

/* LONG and STRUCTURE constants */

/**
* This structure contains useful information for the pixel patterns.
*/
typedef struct Pattern_info {
	
	/*@{*/
	uint8_t width[20]; /**< Contains the width of each pattern. */
	uint8_t value; /**< Contains the pattern in binary. */
	
	uint8_t valid; /**< Contains number of valid values. */
	/*@}*/
	
} Pattern_info;
 
/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */

extern uint8_t width;
extern uint8_t center;

extern uint8_t width2;
extern uint8_t center2;

/* WORDS */

/* LONGS and STRUCTURES */

extern Pattern_info pat_info;
extern Pattern_info pat_info2;

#endif
