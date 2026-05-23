#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"
#include "EEPROM.h"

void Heater_control_fun();

void Heater_control_fun()
{
	if(max1_temperature<=0)
	{
		error_indicate_flg=SET;
		//M_crnt_temp=0;
	}
	if(intial_heating_flg)
	{	
		//if((/*(!hater_setting_password_flg)AND*/(M_crnt_temp>80))OR(M_crnt_temp<80))
		{

			if((max1_temperature<23/*main_set_temp*/)AND(!HEATER))
			{
				heater_on_flg=SET;
				if(heater_on_delay>20)
				HEATER_ON;//MAIN_HTR_ON;	
			}
			else if((max1_temperature>25/*main_set_temp*/))
			{
				HEATER_OFF;//MAIN_HTR_OFF;
				heater_on_flg=CLEAR;
				intial_heating_flg=CLEAR;
			}
		}
		/*else if((hater_setting_password_flg)AND(M_crnt_temp>80))
		{
			MAIN_HTR_OFF;
			heater_on_flg=CLEAR;
		}*/
		
	}
	else if(!intial_heating_flg)
	{
			
			if((coffee_brewing))
			{
				if((max1_temperature<120)AND(!HEATER)AND(water_on_time>0))
				{
					heater_on_flg=SET;
					if(heater_on_delay>5)
					HEATER_ON;//MAIN_HTR_ON;
				}
				else if((max1_temperature>110)OR(water_on_time<=0))
				{
					HEATER_OFF;//MAIN_HTR_OFF;
					heater_on_flg=CLEAR;
					
				}
				
			}

	}
	if(max1_temperature>120)
	{
		HEATER_OFF;//MAIN_HTR_OFF;
		heater_on_flg=CLEAR;
	}

}