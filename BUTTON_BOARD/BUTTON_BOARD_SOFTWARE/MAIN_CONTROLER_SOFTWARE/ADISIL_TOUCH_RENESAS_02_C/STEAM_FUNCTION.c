#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"

void STEAMER_FUNCTION();


void STEAMER_FUNCTION()
{
	if(steamer_start_flg)
	{
		if(steamer_pmp_on_flg)
		{
			if((flow_puluse>10)AND(flow_pulse_check_delay<=0))
			{
				flow_puluse=0;
				flow_pulse_check_delay=0;
				heater_1_on_flg=SET;
				flow_pulse_check_delay=3;
				if(!init_machine_flg)
				{
				ALL_LED_OFF;
				RED_LED_ON;
				}
				if((heater_2_on_flg)AND(hetr_2_on_delay<=0))
				{
					heater_2_on_flg=SET;
				}
				else if (!heater_2_on_flg)
				{
					heater_2_on_flg=SET;
					hetr_2_on_delay=1;				
				}
			
			
			}	
			else if (flow_pulse_check_delay<=0)
			{
				flow_meater_error_flg=SET;
				steamer_pmp_on_flg=CLEAR;
				while(1);			
			}
		
		}
		else if(!steamer_pmp_on_flg)
		{
			ALL_LED_OFF;
			BLUE_LED_ON;
			STEAMER_SOLINOID_ON;
			steamer_pmp_on_flg=SET;
			steaer_pump_pwm_flg=SET;//PUMP_ON
			flow_pulse_check_delay=3;
		
		}
	
	}
	else if(!steamer_start_flg)
	{
			ALL_LED_OFF;
			GREEN_LED_ON;
			steamer_pmp_on_flg=CLEAR;
			steaer_pump_pwm_flg=CLEAR;
			flow_puluse=0;
			flow_pulse_check_delay=0;
			heater_1_on_flg=CLEAR;
			heater_2_on_flg=CLEAR;
			flow_meater_error_flg=CLEAR;
			STEAMER_SOLINOID_OFF;
			DRAIN_SOLINOID_ON;
			drain_delay=3;	
	}
	
}