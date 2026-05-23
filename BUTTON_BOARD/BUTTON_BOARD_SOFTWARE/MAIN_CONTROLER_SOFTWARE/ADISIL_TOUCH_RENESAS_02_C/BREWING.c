#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"
#include "EEPROM.h"

extern void eeprom_write_long_int(unsigned char, unsigned long int);
extern void eeprom_write_int(unsigned char adress,unsigned int value);
extern void eeprom_write(unsigned char address, unsigned char datas);
extern unsigned char eeprom_read(unsigned char);
extern unsigned int eeprom_read_int(unsigned char);
extern unsigned long int eeprom_read_long_int(unsigned char);

void coffee_brewing_fun()
{
	if(coffee_brewing)
	{
		if(intial_cof_brew_flg)
		{
			if(cof_brewing_cycle>=0)
			{
				if(cof_brew_on_flg)
				{
					if(/*(cof_brewing_on_time<=0)OR */(cof_flow_plus<=0))
					{
						if(cof_brew_delay_flg)
						{
							if(cof_interval_time<=0)
							{ 
								if(cof_brewing_cycle>0)
								{
									cof_brew_on_flg=CLEAR;
									cof_brew_delay_flg=CLEAR;
								}
								else
								{
									if(cof_dec_flush_flg)
									{
										if(cof_dec_on_time<=0)
										{

											intial_cof_brew_flg=CLEAR;
											cof_brew_on_flg=CLEAR;
											cof_brew_delay_flg=CLEAR;
											cof_dec_flush_flg=CLEAR;
																								
											gram_change_flg=cof_brew_start_flg=coffee_brewing=CLEAR;
											BREW_COMPLETE_RGB;
											//brewing_conform_flg=CLEAR;
											eeprom_write(eeprom_cof_brew_start_flg,cof_brew_start_flg);
											eeprom_write(eeram_gram_change_flg,gram_change_flg);
											//brewing_complete_flg = SET;

										}
									}
									else
									{
										cof_dec_flush_flg=SET;

									}
								}
							}

						}
						else
						{
							//COF_BREWER_OFF;
							flow_meter_pulse_flg = CLEAR;
							pump_pwm_flg = CLEAR;
							PUMP =  0;
							cof_brew_delay_flg=SET;
							cof_interval_time=60;
							if(cof_brewing_cycle>0)
							cof_brewing_cycle--;
							cof_brew_remining_cly=cof_brewing_cycle;
							eeprom_write(eeprom_cof_brew_remining_cly,cof_brew_remining_cly);
							

							
						}
					}

				}
				else
				{
					cof_brew_on_flg=SET;
					flow_meter_pulse_flg = SET;
					if(gram_change_flg)///////////200 G setting///////
					{
						//pump_on_pluse = 772;//600;//486;
						cof_brewing_time=333;//390;//166;//total pulse - 83//eeprom_read(eeprom_cof_brew_on_time);			
						
					}
					else///////////////500G setting
					{
						cof_brewing_time=666;//666;//total pulse - 207;
						
						//pump_on_pluse = 1200; //final -- 1200;//1426;//1399;//1043;    ///400G -- 960  (or) 1000						
					}

          			 	cof_flow_plus=(cof_brewing_time);
					cof_flow_plus=(cof_flow_plus*BIG_SMALL_FLOW_METER);
					if((cof_brewing_time>0) OR (pump_on_pluse>0))
					{
						pump_pwm_flg = SET;
					}
					
				}
//				else
//				{
//					brew_pause_flg=SET;
//
//				}
			}
		}
		else
		{
			//star_update_count=0;
			intial_cof_brew_flg=SET;
			brewing_on_time=eeprom_read_int(eeram_brewing_on_time);
			
			if(!(GM_500_ENABLE)){	
				cof_brew_remining_cly=cof_brewing_cycle=3;
			}
			else{
				cof_brew_remining_cly=cof_brewing_cycle=3;//6;
			}
			//D_Setting[eeprom_first_cof_brew_cycles]=D_Setting[eeprom_cof_brew_remining_cly]=cof_brewing_cycle;
			eeprom_write(eeprom_cof_brew_remining_cly,cof_brew_remining_cly);
			
			cof_brew_start_flg=coffee_brewing;
			eeprom_write(eeprom_cof_brew_start_flg,cof_brew_start_flg);
			eeprom_write(eeram_gram_change_flg,gram_change_flg);
			
		}
	}
}
