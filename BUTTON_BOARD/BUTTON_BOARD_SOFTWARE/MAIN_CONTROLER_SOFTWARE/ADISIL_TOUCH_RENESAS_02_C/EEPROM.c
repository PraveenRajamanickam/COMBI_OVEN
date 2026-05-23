#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"


unsigned char eeprom_read(unsigned char);
void eeprom_write(unsigned char address, unsigned char datas);
void eeprom_write_int(unsigned char,unsigned int);
unsigned int eeprom_read_int(unsigned char);
extern __boolean read_iic(unsigned char, unsigned char);
extern __boolean write_iic(unsigned char, unsigned char);
unsigned long int eeprom_read_long_int(unsigned char);
void eeprom_write_long_int(unsigned char, unsigned long int);
unsigned char eeprom_read(unsigned char);

unsigned int b,ep,eeprom_write_time_out;
__boolean eeprom_write_ok,eeprom_reed_ok;

void eeprom_write(unsigned char address, unsigned char datas)
{
	for(ep=0;ep<=20;ep++)
	{
		eeprom_write_time_out=20;
		do
		{
			tmp_var = datas;	//value to write in eeprom
			ram_addr = &tmp_var;
			disp_addr = address;	//write at 0th address
			eeprom_write_ok=write_iic(EEPROM_WRITE,1);
			//eeprom_delay = 500;//1000;	//100usec isr
			//eeprom_waiting();
			eeprom_ten_msec_delay = 5;			//100usec isr
			while(eeprom_ten_msec_delay);
			eeprom_write_time_out--;	
		}
		while((!eeprom_write_ok)AND(eeprom_write_time_out));	
		tmp_var=0;
		for(b = 0; b < 30 ; b++)
		{
			tmp_var = 0;	//clear that variable
			ram_addr = &tmp_var;
			disp_addr = address;	//read at 0th address
			eeprom_reed_ok=read_iic(EEPROM_READ,1);
			//eeprom_delay = 250;//500;	//100usec isr
			//eeprom_waiting();	
			eeprom_ten_msec_delay = 3;			//100usec isr
			while(eeprom_ten_msec_delay);
			if(eeprom_reed_ok)
			break;	
		}	
		if(tmp_var==datas)
		{
			ep=100;
			break;
		}
	}
}
unsigned char eeprom_read(unsigned char address)
{
	for(b = 0; b < 30 ; b++)
	{
		tmp_var = 0;	//clear that variable
		ram_addr = &tmp_var;
		disp_addr = address;	//read at 0th address
		eeprom_reed_ok=read_iic(EEPROM_READ,1);
		//eeprom_delay = 600;//500;	//100usec isr
		//eeprom_waiting();	
		eeprom_ten_msec_delay = 6;			//100usec isr
		while(eeprom_ten_msec_delay);
		if(eeprom_reed_ok)
		break;	
	}				
	return(tmp_var);
}

void eeprom_write_int(unsigned char adress,unsigned int value)
{
	unsigned char temp_count;
	temp_count = (char)value;//LSB
	eeprom_write(adress,temp_count);
	temp_count = (char)(value>>8);//MSB
	adress++;
	eeprom_write(adress,temp_count);	
}

unsigned int eeprom_read_int(unsigned char adress)
{
	unsigned char temp_char;
	unsigned int temp_int;
	temp_char=eeprom_read(adress);	
	adress++;
	temp_int=eeprom_read(adress);
	temp_int <<=8;
	temp_int |=	temp_char;
	return(temp_int);
}

void eeprom_write_long_int(unsigned char address, unsigned long int datas)
{
	unsigned char temp_count;
	
	temp_count = (char)(datas >> 24);  //MSB
	eeprom_write(address,temp_count);	
	temp_count = (char)(datas >> 16);  //MSB
	address ++;
	eeprom_write(address,temp_count);
	temp_count = (char)(datas >> 8);  //MSB
	address ++;
	eeprom_write(address,temp_count);
	temp_count = (char)datas;   //LSB
	address ++;
	eeprom_write(address,temp_count);		
}

unsigned long int eeprom_read_long_int(unsigned char address)
{
	unsigned char temp_char;
	unsigned long int temp_long_int1, temp_long_int2,temp_long_int3;
	temp_long_int1 = eeprom_read(address);	
	temp_long_int1 <<= 24;
	temp_long_int2 = eeprom_read(address+1);	
	temp_long_int2 <<= 16;
	temp_long_int3 = eeprom_read(address+2);	
	temp_long_int3 <<= 8;
	temp_char = eeprom_read(address+3);
	temp_long_int1 |= (temp_long_int3|temp_long_int2 | temp_char);
	return(temp_long_int1);
}