#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"


void clock (void);
void iic_delay (unsigned char);
void start_iic (void);
void stop (void);
__boolean  ack (void);
void write_byte (void);
void rec_data (void);
void send_ack (char);
__boolean read_iic(unsigned char , unsigned char );
__boolean write_iic(unsigned char , unsigned char );
void data_trans(unsigned char , unsigned char);

__boolean ack (void)
{
	//__boolean ack_received_flag;
	
	SDA_INPUT;//SDA;
	//pd2_1=0;
	SDA = 1;
	iic_delay(0x0F);
	
	ACC = 0x3F*0x0f;//*0x0a;	//for renesas
	while (ACC)
	{
		//asm("clrwdt");
		ACC--;
		if (SDA == 0)//slave pulls SDA=0,when all datas are received by slave;
		{
			ack_received_flag = 1;
			break;
		}
		else
		{
			ack_received_flag = 0;
		}
	}	
	
	SCL = HIGH;
	iic_delay(0x7);
	SCL = 0;
	iic_delay(0x7);
	//TRISC = 0X06;
	SDA_OUTPUT;
	//pd2_1=1;
	return ack_received_flag;
} 

 
void start_iic (void)
{
	SCL = 1;
	SDA = 1;//falling edge of SDA when SCL=1;
	iic_delay(0x0F);

	SDA = 0;
	iic_delay(0x1F);

	SCL = 0;
	iic_delay(0x07);
}


void stop (void)
{
	SDA = 0;
	iic_delay(0x0F);//rising edge of SDA when SCL=1;

	SCL = 1;
	SDA = 0;
	iic_delay(0x0F);

	SDA = 1;
	iic_delay(0x0F);
}



__boolean write_iic(unsigned char device_addr, unsigned char no_bytes) 
{
	unsigned char temp;
	temp_pr[1] = disp_addr;//unsigned int has 2 bytes of address;
	temp_pr[0] = disp_addr>>8;
	start_iic();
	data_trans(device_addr, 0x08);//adress of the device;
	if (! ack())
	{
		stop();
		return(0);
	}
   	data_trans(temp_pr[1], 0x08);//memory location address in the device;	
	if (! ack())
	{
		stop();//no ack;
		return(0);
	}
   
	temp = 0;
	do
	{
	//	asm("clrwdt");
		data_trans(*ram_addr, 0x08);//data;
		if ( ! ack() )
		{
			stop();
			return(0);			
		}
		temp++;
		ram_addr++;
	}while (temp < no_bytes);

   	stop();
	if(SDA == LOW)//after ack,then SDA pulls up to 1;
   	{
	   	SDA = 1;
       		iic_delay(0x5f);
	}
	return(1);
}                    
__boolean read_iic(unsigned char device_addr, unsigned char no_bytes)
{
	unsigned char temp;
	temp_pr[1] = disp_addr;
	temp_pr[0] = disp_addr>>8;

	start_iic();
	/* DUMMY WRITE  */
	data_trans((device_addr & 0xFE), 0x08);
	if ( ! ack() )		
	{
		stop();
		return(0);
	}	

	/* Send the address to be read */
  	data_trans(temp_pr[1],0x08);
	if ( ! ack() )		
	{
		stop();
		return(0);
	}	
	
	stop();
    iic_delay(0x3f);

	/*Send the start condition once again */
	start_iic();
	/*Select the device for reading */
	data_trans(device_addr, 0x08);
	if ( ! ack() )		
	{
		stop();
		return(0);
	}	

	/*Initialise address pointer */
	temp = 1;
	while(1)
	{
		//asm("clrwdt");
		clock_low_flag = SET;
		receive_bit_counter = 1;
		received_data = 0;
		//TRISC = 0X16;
		SDA_INPUT;
	//	pd2_1=0;
		rec_data();
		//TRISC = 0X06;
		SDA_OUTPUT;
	//	pd2_1=1;
		*ram_addr = received_data;
		temp++;
		if (temp > no_bytes)
		{
			send_ack(0);
			stop();	
			return(1);
		}
		else
		{
			send_ack(1);
			ram_addr++;
		}			
	}
}


void clock (void)
{
	SCL = 1;
	iic_delay(0x07);//high to low;
	SCL = 0;
	iic_delay(0x07);
}


void iic_delay(unsigned char time)
{
	ACC = time*0x0f;//*0x0a;	//for renesas
	while (ACC)
	{
		ACC--;
		//asm("clrwdt");
	}
}


/* To read the data. SDA status will be read at the middle of clock high.
	Received data will be in received data area. */

void rec_data (void)
{
	while (1)
	{
	//	asm("clrwdt");
		if (clock_low_flag == SET)
		{
			clock_low_flag = CLEAR;
			SCL = HIGH;
			iic_delay(0x0f);	//0X0F
			sda_status_flag = CLEAR;
			if (SDA == HIGH)
			{
				sda_status_flag = SET;
			}
			iic_delay(0x0f);	//0X0F
		}
		else
		{
			clock_low_flag = SET;
			SCL = LOW;
			ACC = received_data;
			ACC = ACC << 1;
			if(sda_status_flag)
			{
				ACC |= 0x01;
			}
			received_data = ACC;
			receive_bit_counter++;
			if(receive_bit_counter > 8)
				break;
			iic_delay(0x0f);
		}	
	}
}



/* To send acknowledgement by referring status for read. If reading is 
	complete, acknowlegement will not be send */


void send_ack (char status)
{
	SCL = LOW;
	iic_delay (0x0F);
	if (status == HIGH)
		SDA = LOW;
	else
		SDA = HIGH;
	iic_delay (0x0F);
	SCL = HIGH;
	iic_delay (0xF);
	iic_delay (0xf);
	SCL = LOW;
	iic_delay (0x0F);	
	SDA = HIGH;
	iic_delay (0x0F);
}

void data_trans(unsigned char tr_data, unsigned char tmp_bits)
{
	unsigned char tmp_tr_data,tmp_tr_data1;
	
	while (tmp_bits)   //changing of msb into lsb,bcoz msb is trd first and then trd;
	{			
		tmp_tr_data = tr_data;		//tmp_tr_data is just used as a variable not as eeprom address
  		tmp_tr_data1 = tmp_tr_data;
		tmp_tr_data1 >>=7;
		SDA = tmp_tr_data1;
		tr_data = tmp_tr_data<<1;
		iic_delay(0x03);	//3F);	
		clock();
		tmp_bits--;		
	}
}