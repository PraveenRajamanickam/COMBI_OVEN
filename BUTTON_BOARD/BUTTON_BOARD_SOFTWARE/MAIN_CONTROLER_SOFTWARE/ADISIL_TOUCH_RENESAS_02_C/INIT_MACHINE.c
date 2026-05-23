#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"
extern void check_and_water_fill();
extern void Heater_control_fun();
extern void MAX1_THERMOCOUPLER();
void INIT_MACHINE();
void INIT_MACHINE()
{
	inite_machine_flg=SET;
	while(inite_machine_flg)
	{
//		if(one_sec_temperature_delay_flg)
//	       	{
//		       MAX1_THERMOCOUPLER(); 
//		       one_sec_temperature_delay_flg = CLEAR;
//	        }
		check_and_water_fill();		
	}
	intial_heating_flg = CLEAR;
	while(intial_heating_flg)
	{
//		if(one_sec_temperature_delay_flg)
//	        MAX1_THERMOCOUPLER();
		check_and_water_fill();
		Heater_control_fun();
	}
	if(coffee_brewing)
	{
		//intial_brewing_update_flg=SET;
		intial_cof_brew_flg=SET;
		if(cof_brewing_cycle<=0)
		{
			intial_cof_brew_flg=SET;
			cof_brew_on_flg=SET;
			cof_brew_delay_flg=SET;
			cof_dec_flush_flg=SET;
		}
	}
}