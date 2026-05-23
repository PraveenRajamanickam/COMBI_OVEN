#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"
#include "math.h"
void hundK_temp_func();

void hundK_temp_func()
{
	 if(!R_AND_D_MODE)
	 {
		 if((ad_result1>1020) OR (ad_result1<=0))
		 {
			 temperature_err_flg = SET;
		 }
		 logR2 = log( R1 * (1023.0 /(float)(1023-ad_result1) - 1.0));
	  	 max1_temperature= M_crnt_temp = top_max_temperature = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2))- 273.15;
	 }
	 else 
	 {
		max1_temperature  = M_crnt_temp = top_max_temperature = 130;
	 }
}
//void MAX1_THERMOCOUPLER();
//unsigned char spiread();
//void one_Msec_wait_fun();
//
//void MAX1_THERMOCOUPLER()
//{
//	float max_temperature;
//	_v_= 0;
//	MAX1_CS=0;
//	one_msec_wait_delay=10;
//	one_Msec_wait_fun();
//	_v_ = spiread();
//	
//	_v_<<=8;
//	v_= spiread();
//	
//	_v_ = v_ + _v_;
//	MAX1_CS=1;
//	
//	if(_v_ & 0x04)
//	{
//		max_temperature = 0;
//	}
//	else
//	{
//		_v_=_v_>>3;
//		max_temperature = _v_*0.25;
//	}
////	if(R_AND_D_MODE)
////	max1_temperature=65;
////	else 
//	max1_temperature = max_temperature;
//	one_sec_temperature_delay_flg = CLEAR;
//	if(max1_temperature<=0)
//	{
//		temper_err_count++;
//		if(temper_err_count>=3)
//		{
//			temperature_err_flg = SET;
//			pump_pwm_flg = CLEAR;
//			ALL_OUTPUT_OFF;
//			TEMPE_ERROR_LED;
//			while(1);
//		}
//	}
//}
//
//
//
//unsigned char spiread()
//{
//	int _i_=0;
//	unsigned char _d_=0;
//	for (_i_=7;_i_>=0;_i_--)
//	{		
//		MAX_SCK=0;
//		one_msec_wait_delay=10;
//		one_Msec_wait_fun();
//		if(MAX_SO)
//		{
//			_d_|=(1<<_i_);
//		}
//		MAX_SCK=1;
//		one_msec_wait_delay=10;
//		one_Msec_wait_fun();
//		
//	}
//	return _d_;
//}
//
//void one_Msec_wait_fun()
//{
// 	while(one_msec_wait_delay)
//	{
//		if(one_msec_wait_delay<=0)
//		break;
//	}
//}

