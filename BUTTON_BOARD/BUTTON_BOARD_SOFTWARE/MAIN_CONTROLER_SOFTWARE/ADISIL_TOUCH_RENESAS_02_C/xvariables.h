
extern __boolean
eeprom_save_flg,
relay_flg;

extern unsigned char
cleaning_feed_timer,
touch_interval_timer,
touch_press_counter;


/****************************************************** I2C&EEPROM  ***************************************/
extern __boolean
ack_received_flag,
sda_status_flag,
clock_low_flag;

///////////////////100k temperature sensor
extern unsigned int top_max_temperature,M_crnt_temp;
extern int tCelsius;
extern float logR2, R2;

extern unsigned char
//ten_msec_counter,
eeram_addr,
eeram_temp_data,
received_data,
temp_pr[3],
receive_bit_counter,
*ram_addr,
tmp_var;

extern unsigned int 
eeprom_ten_msec_delay,
ACC,
disp_addr;

////////////////////////////////////////////////////////
extern unsigned char 
D_Setting[260];

////////////////////////WATER LEVEL/////////////
extern unsigned char 
main_refill_on_time,
main_refill_off_time;

extern __boolean 
main_refilling_start_flg;

extern unsigned int
minimum_5ml_counter;

///////////////////////INIT MACHINE...//////////
extern __boolean 
intial_heating_flg,
inite_machine_flg;
extern unsigned char 
initial_delay_timer,
main_refill_on_time,
main_refill_off_time;
///////////////////////HEATER/////////////
extern unsigned char
upper_flowmeter_counter,
lower_flowmeter_counter,
silicon_heater_on_delay,
silicon_heater_off_delay,
temper_err_count,
heater_on_delay,
caliberatiom_nagative_sign_flag,
calibration_temperature,
main_reset_temp,
main_set_temp;

extern __boolean
err_led_blink_flg,
upper_flowmeter_flg,
upper_flowmeter_error_flg,
lower_flowmeter_error_flg,
silicon_heater_on_flg,
temperature_err_flg,
heater_on_flg,
error_indicate_flg;
//////////////////////KEY DATA////////
extern unsigned char key_press_delay,
temp_key,
press_key,
confirm_key;

extern __boolean
confirm_key_press_flg,
new_key_flg,
speed1_inc_dec_flag,
speed2_inc_dec_flag,
key_pressed_conform_flag,
key_scan_delay_flag,
key_status_changed_flag;

extern unsigned char
key_scan_delay,
key_scan_data,
temp_key_scan_data,
temp_key_status,
key_status,
speed_inc_dec;


//////////////////////BREWING.../////////////
extern unsigned int
one_sec_brew_pulse,
final_onesec_brew_pulse,
cof_flow_plus,
water_on_time,
cof_dec_on_time,
cof_interval_time,
save_cof_cups,
brewing_on_time,
interval_time,
cof_brewing_time,
brewing_dec_on_time,
brwwing_gram;


extern unsigned char
brewing_err_counter,
pump_on_pluse,
total_cb_cyl,
cof_brew_remining_cly,
cof_brewing_cycle,
cb_50_cyl,
cb_250_cyl,
cb_200_cyl,
cb_150_cyl,
cb_100_cyl;

extern __boolean
brewing_err_counter_flg,
brewing_flowmeter_err_flg,
brew_complete_flg,
blink_flg,
pump_start_flg,
cof_dec_flush_flg,
cof_brew_delay_flg,
cof_brew_on_flg,
intial_cof_brew_flg,
coffee_brewing,
cof_brew_start_flg,
gram_change_flg,
first_time_brewing_flg;

/********************MAX6675******************/
extern __boolean
one_sec_temperature_delay_flg;
extern unsigned int
max1_temperature,
max2_temperature;
extern unsigned int
b_,
_b_,
v_,
_v_;

extern unsigned char 
one_msec_wait_delay;

//////////////////////////////TIMER//////////////////
extern unsigned int
one_minite_counter,one_second_counter,hundred_msec_counter,one_msec_counter,hundred_usec_counter,ten_msec_counter,half_second_counter;

//////////////////////////PWM
/*******************PWM*************/
extern unsigned char
PUMP_OFF_TIME,
PUMP_ON_TIME,
pump_pulse;
extern __boolean
pump_pwm_flg,
pump_pulse_on_flg;
///////////////////flowmeter
extern __boolean 
flow_meter_pulse_flg;

/************************ADC********************/
extern __boolean
adc_reading_delay_flag;
extern unsigned char
adc_selector_count;
extern unsigned int
ad_result1;


