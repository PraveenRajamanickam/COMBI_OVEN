/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_adc_user.c
* Version      : CodeGenerator for RL78/G13 V2.05.06.02 [08 Nov 2021]
* Device(s)    : R5F100FE
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for ADC module.
* Creation Date: 6/20/2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTAD r_adc_interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_adc.h"
/* Start user code for include. Do not edit comment generated here */
#include "macros.h"
#include "xvariables.h"

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_adc_interrupt
* Description  : This function is INTAD interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_adc_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
     if(adc_reading_delay_flag)
    {
	    adc_reading_delay_flag=CLEAR;
	    if(!TESTING_DISPLAY_MODE)
	    {
		   // if(adc_selector_count==1)
		   // R_ADC_Get_Result(&ad_result2);
//		    if(adc_selector_count==1)
//		    R_ADC_Get_Result(&ad_result1);
		   
		  //  else if(adc_selector_count==4)
		   // R_ADC_Get_Result(&ad_result4);
		   if(adc_selector_count==1)
		    R_ADC_Get_Result(&ad_result1);
	    
	    }
	    else if(TESTING_DISPLAY_MODE)
	    {
			ad_result1=600;
		//ad_result3=600;
	    }
	    
	    
	   /* else if((adc_selector_count==5)AND((COF_DEC_FRW)OR(COF_DEC_REV)))
	    R_ADC_Get_Result(&cs_result1);
	    else if((adc_selector_count==6)AND((MILK_FRW)OR(MILK_REV)))
	    R_ADC_Get_Result(&cs_result2);
	    else if((adc_selector_count==7)AND((TEA_DEC_FRW)OR(TEA_DEC_REV)))
	    R_ADC_Get_Result(&cs_result3);*/
	    
	   /* if((adc_selector_count==5)AND((COF_DEC_FRW)OR(COF_DEC_REV)))
	    R_ADC_Get_Result(&cs_result1);
	    if((adc_selector_count==6)AND((MILK_FRW)OR(MILK_REV)))
	    R_ADC_Get_Result(&cs_result2);
	    if((adc_selector_count==7)AND((TEA_DEC_FRW)OR(TEA_DEC_REV)))
	    R_ADC_Get_Result(&cs_result3);
	    if((adc_selector_count==8)AND(COF_BREWER))
	    R_ADC_Get_Result(&cs_result4);
	    if((adc_selector_count==9)AND(HOTWATER))
	    R_ADC_Get_Result(&cs_result5);
	    if((adc_selector_count==10)AND(TEA_BREWER))
	    R_ADC_Get_Result(&cs_result6);
	    if((adc_selector_count==11)AND(MAIN_REFILLING))
	    R_ADC_Get_Result(&cs_result7);
	    if((adc_selector_count==12)AND(MILK_MIX_PUMP))
	    R_ADC_Get_Result(&cs_result8);
	    if((adc_selector_count==13)AND(WAR_REFILLING))
	    R_ADC_Get_Result(&cs_result9);*/
	    
	    if(++adc_selector_count>3)
	    {
			adc_selector_count=1;
	    }
	    if(adc_selector_count==1)
	    ADS = 0x03;
	    else if(adc_selector_count==2)
	    ADS = 0x01;
	    else if(adc_selector_count==3)
	    ADS = 0x02;
	 }
	 /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
