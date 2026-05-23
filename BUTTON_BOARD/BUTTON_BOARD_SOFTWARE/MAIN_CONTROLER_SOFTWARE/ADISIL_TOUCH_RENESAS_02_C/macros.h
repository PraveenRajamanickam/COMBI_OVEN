#define SET 	  1
#define CLEAR	  0
#define HIGH      1
#define LOW       0
#define ON        1 
#define OFF       0
#define AND       &&
#define OR        ||
#define EQUAL_TO  ==
#define NOT_EQUAL_TO !=

#define TOUCH_BUTTON		P13.7
#define RELAY			P7.0
#define CLEANING_FEEDBACK	P2.6


#define GM_500_ENABLE    1

#define BIG_SMALL_FLOW_METER	 8.3 //5.62///small=1.57//big=2.25//new200=5.62

#define R_AND_D_MODE			0

#define TESTING_DISPLAY_MODE   0

#define _200G_BUTTON     P4.1
#define _500G_BUTTON	P1.1

#define  R1  10000
#define  c1  1.009249522e-03
#define  c2  2.378405444e-04
#define  c3  2.019202697e-07

//////////////////RGB MACROS//////////////
#define  RED_250G   P1.2
#define  BLUE_250G  P2.7
#define  GREEN_500G P14.6
#define  RED_500G   P14.7


#define BREW_250_RGB       RED_250G = 0, BLUE_250G = 1;
#define BREW_500_RGB       RED_500G = 0, GREEN_500G =1;
#define BREW_COMPLETE_RGB  RED_250G = RED_500G = 1, BLUE_250G = GREEN_500G = 0, brew_complete_flg = 1;
#define REFILL_ERROR_LED   RED_250G = BLUE_250G = 0, RED_500G = GREEN_500G = 1;
#define TEMPE_ERROR_LED    RED_250G = BLUE_250G = 1, RED_500G = GREEN_500G = 0;
#define BREWING_ERROR_LED  RED_250G = BLUE_250G =  RED_500G = GREEN_500G = 0;

/***************I2C*****************/
#define SCL			P3.0	
#define SDA			P5.0
#define SDA_INPUT		PM5.0=1 
#define SDA_OUTPUT		PM5.0=0

#define DEFAULT_VALUE_SET		0x37

//#define STEAM_PUSH_BUTTON	P2.6

/////////////MAX6675///////
#define MAX_SCK		P1.5
#define MAX_SO		P1.4
#define MAX1_CS		P1.6
#define MAX2_CS 	P1.7

/***********EEPROM*************/
#define EEPROM_WRITE    	0xa6
#define EEPROM_READ     	0Xa7


/***********OUTPUTS*************/
#define HEATER		P7.2
#define PUMP		P7.3
#define PTC		P7.1

#define  HEATER_ON	HEATER=1
#define  HEATER_OFF	HEATER=0


#define  PUMP_ON	PUMP=1
#define  PUMP_OFF	PUMP=0

#define ALL_OUTPUT_OFF  PUMP = HEATER = PTC =  CLEAR;

/*
#define  BREWING_PUMP	 	P7.3  //HEATER2 
#define  BREWING_PUMP_ON	BREWING_PUMP=1
#define  BREWING_PUMP_OFF	BREWING_PUMP=0

#define  HEAYER_2_ON		BREWING_PUMP=1
#define  HEAYER_2_OFF   	BREWING_PUMP=0

#define  STEAMER_SOLINOID	P5.1
#define  STEAMER_SOLINOID_ON	STEAMER_SOLINOID=1
#define  STEAMER_SOLINOID_OFF	STEAMER_SOLINOID=0

#define  DRAIN_SOLINOID		P7.0
#define  DRAIN_SOLINOID_ON	DRAIN_SOLINOID=1
#define  DRAIN_SOLINOID_OFF	DRAIN_SOLINOID=0

#define  ALL_LED_ON		BLUE_LED_ON,RED_LED_ON,GREEN_LED_ON
#define  ALL_LED_OFF		BLUE_LED_OFF,RED_LED_OFF,GREEN_LED_OFF


#define  PTC_HEATER		P2.7
#define  PTC_HEATER_ON		PTC_HEATER=1
#define  PTC_HEATER_OFF		PTC_HEATER=0

#define  BLUE_LED_ON		PTC_HEATER=0
#define  BLUE_LED_OFF		PTC_HEATER=1

#define  RED_LED		P1.2
#define  RED_LED_ON		RED_LED=0
#define  RED_LED_OFF		RED_LED=1

#define  GREEN_LED		P1.3
#define  GREEN_LED_ON		GREEN_LED=0
#define  GREEN_LED_OFF		GREEN_LED=1


/**********************UART1***************/
//#define ACKNOLDGMENT uart1_buffer[0]='*',uart1_buffer[1]='A',uart1_buffer[2]='C',uart1_buffer[3]='K',uart1_buffer[4]='#',data_transmit_flg=SET;
//#define FLOWMETR_ERROR  uart1_buffer[0]='*',uart1_buffer[1]='F',uart1_buffer[2]='E',uart1_buffer[3]='R',uart1_buffer[4]='#',data_transmit_flg=SET;

