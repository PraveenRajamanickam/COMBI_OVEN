#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"
#include "eeprom.h"
void check_and_water_fill();
void flow_meter_err_func();

void check_and_water_fill()
{
	//Main_water_level_conform();
	flow_meter_err_func();
	if(inite_machine_flg)
	{
		if((main_refill_on_time<=16)AND(!pump_pwm_flg))
		{
			pump_pwm_flg = SET;
			minimum_5ml_counter = 20*8.3;
			//PUMP_ON;//MAIN_REFILLING_ON;
			//UP_FAN_ON;
		}
		else if((main_refill_on_time>=16)AND(PUMP)AND(minimum_5ml_counter<=0))
		{
			inite_machine_flg=CLEAR;
			pump_pwm_flg = CLEAR;
			PUMP_OFF;//MAIN_REFILLING_OFF;
			///UP_FAN_OFF;
		}
	}

	else if((cof_flow_plus>0))
	{
		//if((coffee_brew_state_flg)/*OR(water_on_time>0)*/OR(tea_brew_state_flg))
		//{
			if(pump_start_flg)
			{
				if(water_on_time<=0)
				{
					HEATER_OFF;
					PUMP_OFF;//MAIN_REFILLING_OFF;
					pump_pwm_flg=CLEAR;
					pump_pulse=CLEAR;
					pump_pulse_on_flg=CLEAR;
					pump_start_flg=CLEAR;
					cof_flow_plus = water_on_time;
					
				}
			}
			else 
			{
				///UP_FAN_OFF;
				//HOTWATER_OFF;
				pump_start_flg=SET;
				pump_pwm_flg=SET;
				if(cof_flow_plus>0)
				water_on_time=cof_flow_plus;
				
				if(water_on_time>0)
				PUMP_ON;//MAIN_REFILLING_ON;
			}
		//}
	}
}

void flow_meter_err_func()
{
	
	if(lower_flowmeter_counter>=10)
	{
		lower_flowmeter_error_flg = SET;
	}
	if(upper_flowmeter_counter>=10)
	{
		upper_flowmeter_error_flg = SET;
	}
	if((final_onesec_brew_pulse<20)AND(coffee_brewing)AND(water_on_time>0))
	{
		brewing_err_counter_flg = SET;
		if(brewing_err_counter>2)
		{
			brewing_flowmeter_err_flg = SET;
		}
	}
	else
	brewing_err_counter_flg  = CLEAR;
	while((upper_flowmeter_error_flg)OR(lower_flowmeter_error_flg)OR(brewing_flowmeter_err_flg))
	{
		pump_pwm_flg = CLEAR;
		ALL_OUTPUT_OFF;
		if(upper_flowmeter_error_flg)
		{
			RED_500G = HIGH;
			if(err_led_blink_flg)
			GREEN_500G = HIGH;
			else
			GREEN_500G = LOW;
		}
		if((lower_flowmeter_error_flg)OR(brewing_flowmeter_err_flg))
		{
			RED_250G = HIGH;
			if(err_led_blink_flg)
			BLUE_250G = HIGH;
			else
			BLUE_250G = LOW;
		}
		
	}
}