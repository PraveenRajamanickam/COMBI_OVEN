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
* File Name    : r_cg_timer_user.c
* Version      : CodeGenerator for RL78/G13 V2.05.06.02 [08 Nov 2021]
* Device(s)    : R5F100FE
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for TAU module.
* Creation Date: 6/20/2025
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTTM00 r_tau0_channel0_interrupt
/* Start user code for pragma. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
#include "macros.h"
#include "xvariables.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern void pump_pwm_fn();
extern void uart1_tx_fun();
extern void hundK_temp_func();///////////////////100k	 
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_tau0_channel0_interrupt
* Description  : This function is INTTM00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel0_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    	
    	if(++hundred_usec_counter>2)
	{
		hundred_usec_counter=0;
		if(pump_pwm_flg)
         	pump_pwm_fn();
	
		
		
		
	}
	if(++one_msec_counter>20)
	{
		one_msec_counter = 0;
		if(one_msec_wait_delay>0)
		one_msec_wait_delay--;
		
	}
	if(++ten_msec_counter>10)
	{
		ten_msec_counter = 0;
		if(eeprom_ten_msec_delay>0)
		{
			eeprom_ten_msec_delay--;
		}
		if(key_scan_delay_flag)
		{
			key_scan_delay++;
		}	
	
	}
	
	if(++hundred_msec_counter>2000)
	{
		hundred_msec_counter=0;
		
		if((TOUCH_BUTTON)AND(touch_press_counter<30)AND(touch_interval_timer<=0))
		   {
			   touch_press_counter++;
		   }
		   else if(!TOUCH_BUTTON)
		   {
			  touch_press_counter=0; 
		   }
		   
		   if(touch_press_counter>=20)
		   {
			   relay_flg=!relay_flg;
			   touch_press_counter=0;
			   if(relay_flg)
			   RELAY=1;
			   else 
			   RELAY=0;
			   touch_interval_timer=30;
			   eeprom_save_flg = SET;
		   }
		
		    //////////////////////////main htr/////////////////////////
		    if((heater_on_flg)AND(heater_on_delay<25))
		    heater_on_delay++;
		    else if(!heater_on_flg)
		    heater_on_delay=0;
		    adc_reading_delay_flag=SET;
	            
		
		if(++half_second_counter>5)
		{
			half_second_counter = 0;
			hundK_temp_func();///////////////////100k	 
			if((coffee_brewing)AND(water_on_time>0))
			{
				final_onesec_brew_pulse = one_sec_brew_pulse;
				one_sec_brew_pulse = 0;
				if(brewing_err_counter_flg)
				brewing_err_counter++;
			}
		}
		if(++one_second_counter>10)
		{
			one_second_counter=0;
			if((!CLEANING_FEEDBACK)AND(cleaning_feed_timer<10))
			   {
				   cleaning_feed_timer++;
			   }
			   else if(CLEANING_FEEDBACK)
			   {
				   cleaning_feed_timer=0;
			   }
			   if(cleaning_feed_timer>5)
			   {
				   relay_flg=CLEAR;
				   cleaning_feed_timer=0; 
				   RELAY=0;
				   touch_interval_timer=30;
				   eeprom_save_flg = SET;
				   
			   }
			   if(touch_interval_timer>0)
		   		touch_interval_timer--;
				
			one_sec_temperature_delay_flg = SET;
			blink_flg =! blink_flg;
			if(initial_delay_timer>0)
			initial_delay_timer--;
			if(cof_interval_time>0)
			cof_interval_time--;
			if(pump_pwm_flg)
			lower_flowmeter_counter++;
			if((pump_pwm_flg)AND(upper_flowmeter_flg))
			upper_flowmeter_counter++;
			if((lower_flowmeter_error_flg)OR(upper_flowmeter_error_flg)OR(brewing_flowmeter_err_flg))
			err_led_blink_flg =!err_led_blink_flg;
			if(++one_minite_counter>60)
			{
				one_minite_counter=0;
				if(silicon_heater_on_delay>0)
				silicon_heater_on_delay--;
				if(silicon_heater_off_delay>0)
				silicon_heater_off_delay--;
			
			}
			

		}
	}
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
