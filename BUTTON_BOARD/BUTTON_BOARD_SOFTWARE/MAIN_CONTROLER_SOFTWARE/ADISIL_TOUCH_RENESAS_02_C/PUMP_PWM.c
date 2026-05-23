#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"

void pump_pwm_fn();

//void pump_pwm_fn()
//{
//	PUMP_ON_TIME = 25;//4;//4;//12;
//	PUMP_OFF_TIME =75;//6;// 6;//120;
//	if(pump_pwm_flg)
//	{
//		pump_pulse++;
//		if(pump_pulse <= PUMP_ON_TIME)
//		{
//			if(!pump_pulse_on_flg)
//			{
//				pump_pulse_on_flg = SET;
//				PUMP = HIGH;
//			}
//		}	
//		else if(pump_pulse<=(PUMP_ON_TIME+PUMP_OFF_TIME))
//		{
//			if(pump_pulse_on_flg)
//			{
//				pump_pulse_on_flg = CLEAR;
//				PUMP = LOW;
//			}
//		}
//		else
//		pump_pulse = 0;		
//		pump_pulse_on_flg = CLEAR;
//		
//
//	}
//	else 
//	PUMP = LOW;
//
//}

void pump_pwm_fn()
{	

		PUMP_ON_TIME=85;
		PUMP_OFF_TIME=15;
	
	if(pump_pwm_flg)
	{
		pump_pulse++;
		if(pump_pulse<=PUMP_ON_TIME)
		{
			if(!pump_pulse_on_flg)
			{
				PUMP = HIGH;
				pump_pulse_on_flg=SET;
			}
		}
		else if(pump_pulse<=(PUMP_ON_TIME+PUMP_OFF_TIME))
		{
			if(pump_pulse_on_flg)
			{
				pump_pulse_on_flg=CLEAR;
				PUMP = LOW;
			}
		}
		else 
		{
			pump_pulse=CLEAR;
			pump_pulse_on_flg=CLEAR;
			PUMP = LOW;
		}
	}
	//if(tea_flow_plus>0)
	//{
		
	//}
	/*else 
	{
		PUMP_ON_TIME=60;
		PUMP_OFF_TIME=40;
	}*/
}