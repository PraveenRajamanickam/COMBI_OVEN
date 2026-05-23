#pragma interrupt INTSR1 uart1_receiver_isr_fun

#include "r_cg_macrodriver.h"
#include "macros.h"
#include "xvariables.h"

extern MD_STATUS R_UART1_Send(uint8_t * const tx_buf, uint16_t tx_num);
void uart1_receiver_isr_fun();
void uart1_tx_fun();
void uart1_receiver_isr_fun()
{
	unsigned char uart_rx1;
	uart_rx1=RXD1;
	keypad_uart_error_clear_count=200;
	uart1_rx_buffer[uart_data++]=uart_rx1;
	if((uart1_rx_buffer[0]=='*')AND(uart1_rx_buffer[4]=='#'))
	{
		if((uart1_rx_buffer[1]=='A')AND(uart1_rx_buffer[2]=='C')AND(uart1_rx_buffer[3]=='K'))
		{
			ack_flg_set=SET;
			uart1_rx_buffer[1]=uart1_rx_buffer[2]=uart1_rx_buffer[3]=0;
		}
		else if((uart1_rx_buffer[1]=='P')AND(uart1_rx_buffer[2]=='T')AND(uart1_rx_buffer[3]=='O'))
		{
			PTC_HEATER_ON;
			ACKNOLDGMENT;
			uart1_rx_buffer[1]=uart1_rx_buffer[2]=uart1_rx_buffer[3]=0;
		}
		else if((uart1_rx_buffer[1]=='P')AND(uart1_rx_buffer[2]=='T')AND(uart1_rx_buffer[3]=='C'))
		{
			PTC_HEATER_OFF;
			ACKNOLDGMENT;
			uart1_rx_buffer[1]=uart1_rx_buffer[2]=uart1_rx_buffer[3]=0;
		}
		else if((uart1_rx_buffer[1]=='S')AND(uart1_rx_buffer[2]=='T')AND(uart1_rx_buffer[3]=='O'))
		{
			steamer_start_flg=SET;
			ACKNOLDGMENT;
			uart1_rx_buffer[1]=uart1_rx_buffer[2]=uart1_rx_buffer[3]=0;
		}
		else if((uart1_rx_buffer[1]=='S')AND(uart1_rx_buffer[2]=='T')AND(uart1_rx_buffer[3]=='C'))
		{
			steamer_start_flg=CLEAR;
			ACKNOLDGMENT;
			uart1_rx_buffer[1]=uart1_rx_buffer[2]=uart1_rx_buffer[3]=0;
			steamer_start_flg=CLEAR;
			steaer_pump_pwm_flg=CLEAR;
			STEAMER_HEATER_OFF;
			STEAMER_SOLINOID_OFF;
			DRAIN_SOLINOID_ON;
			drain_close_time=10;
			stemer_pump_on_flg=CLEAR;
			flow_puluse=0;
			stemer_pump_on_time=0;
		}
		else if((uart1_rx_buffer[1]=='B')AND(uart1_rx_buffer[2]=='R')AND(uart1_rx_buffer[3]=='O'))
		{
			BREWING_PUMP_ON;
			ACKNOLDGMENT;
			uart1_rx_buffer[1]=uart1_rx_buffer[2]=uart1_rx_buffer[3]=0;
		}
		else if((uart1_rx_buffer[1]=='B')AND(uart1_rx_buffer[2]=='R')AND(uart1_rx_buffer[3]=='C'))
		{
			BREWING_PUMP_OFF;
			ACKNOLDGMENT;
			uart1_rx_buffer[1]=uart1_rx_buffer[2]=uart1_rx_buffer[3]=0;
		}
	}

}



void uart1_tx_fun()
{
	if((data_transmit_flg)AND(uart_led_send_delay<=0))
	{
	R_UART1_Send(uart1_buffer,5);
	data_transmit_flg=CLEAR;
	uart_led_send_delay=20;
	}

}