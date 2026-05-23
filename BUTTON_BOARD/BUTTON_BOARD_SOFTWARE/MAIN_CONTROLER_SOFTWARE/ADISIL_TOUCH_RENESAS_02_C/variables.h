
__boolean
eeprom_save_flg,
relay_flg;

unsigned char
cleaning_feed_timer,
touch_interval_timer,
touch_press_counter;

/****************************************************** I2C&EEPROM  ***************************************/
__boolean
ack_received_flag,
sda_status_flag,
clock_low_flag;
///////////////////100k temperature sensor
unsigned int top_max_temperature,M_crnt_temp;
int tCelsius;
float logR2, R2;

unsigned char
//ten_msec_counter,
eeram_addr,
eeram_temp_data,
received_data,
temp_pr[3],
receive_bit_counter,
*ram_addr,
tmp_var;

unsigned int 
eeprom_ten_msec_delay,
ACC,
disp_addr;

////////////////////////////////////////////////////////
unsigned char 
D_Setting[260];

////////////////////////WATER LEVEL/////////////
unsigned char 
upper_flowmeter_counter,
lower_flowmeter_counter,
main_refill_on_time,
main_refill_off_time;

__boolean 
err_led_blink_flg,
upper_flowmeter_flg,
upper_flowmeter_error_flg,
lower_flowmeter_error_flg,
main_refilling_start_flg;

unsigned int
minimum_5ml_counter;

///////////////////////HEATER/////////////
unsigned char
silicon_heater_off_delay,
silicon_heater_on_delay,
temper_err_count,
heater_on_delay,
caliberatiom_nagative_sign_flag,
calibration_temperature,
main_reset_temp,
main_set_temp;
__boolean
silicon_heater_on_flg,
temperature_err_flg,
heater_on_flg,
error_indicate_flg;

///////////////////////INIT MACHINE...//////////
__boolean 
intial_heating_flg,
inite_machine_flg;
unsigned char 
initial_delay_timer,
main_refill_on_time,
main_refill_off_time;



//////////////////////KEY DATA////////
unsigned char
key_press_delay,
temp_key,
press_key,
confirm_key;

__boolean
confirm_key_press_flg,
new_key_flg,
speed1_inc_dec_flag,
speed2_inc_dec_flag,
key_pressed_conform_flag,
key_scan_delay_flag,
key_status_changed_flag;

unsigned char
key_scan_delay,
key_scan_data,
temp_key_scan_data,
temp_key_status,
key_status,
speed_inc_dec;


//////////////////////BREWING.../////////////
unsigned int
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

unsigned char
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

__boolean
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
__boolean
one_sec_temperature_delay_flg;
unsigned int
max1_temperature,
max2_temperature;
unsigned int
b_,
_b_,
v_,
_v_;

unsigned char 
one_msec_wait_delay;


//////////////////////////////TIMER//////////////////
unsigned int
one_minite_counter,one_second_counter,hundred_msec_counter,one_msec_counter,hundred_usec_counter,ten_msec_counter,half_second_counter;

//////////////////////////PWM
/*******************PWM*************/
unsigned char
PUMP_OFF_TIME,
PUMP_ON_TIME,
pump_pulse;
__boolean
pump_pwm_flg,
pump_pulse_on_flg;

///////////////////flowmeter
__boolean 
flow_meter_pulse_flg;


/************************ADC********************/
__boolean
adc_reading_delay_flag;
unsigned char
adc_selector_count;
unsigned int
ad_result1;

