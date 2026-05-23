#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"
void key_scan();
void key_service();

void key_scan()
{
	if(!coffee_brewing)
	{
		if(!key_status_changed_flag)
		{
			//temp_key_scan_data=~P0;		
		  	//key_scan_data = temp_key_scan_data& 0xC0;//0x90;
			if(!_500G_BUTTON)
			key_scan_data = 0x01;
			else if(!_200G_BUTTON)
			key_scan_data = 0x02;
			else 
			key_scan_data = 0x00;
			if(key_scan_data NOT_EQUAL_TO 0)
			{
				if(key_scan_delay_flag)
				{
					if(key_scan_delay>(key_pressed_conform_flag?5:2))
					{
						if(key_scan_data EQUAL_TO temp_key_status)
						{
							key_status = temp_key_status;
							key_status_changed_flag = SET;	
							key_pressed_conform_flag=SET;
						}		
						else
						{
							key_status = 0;
						}
						key_scan_delay_flag = 0;
					}									
				}						
				
				else
				{
					key_scan_delay_flag=SET;
					key_scan_delay=0;
					temp_key_status=key_scan_data;
				}	
			}
			else
			{						
				speed1_inc_dec_flag=CLEAR;
				speed2_inc_dec_flag=CLEAR;
				speed_inc_dec=0;			
				key_pressed_conform_flag=CLEAR;
			}
	  	}
	}
}

void key_service()
{
	if(key_status_changed_flag)
	{	
		key_status_changed_flag=0;
		if(key_status == 0x02)//200
		{
			gram_change_flg = SET;
			coffee_brewing = SET;
		  			
		}
		else if(key_status== 0x01)//500
		{
			gram_change_flg = CLEAR;
			coffee_brewing = SET;
		}
		key_status = 0;
	}
}