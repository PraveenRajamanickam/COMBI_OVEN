#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "EmonLib.h"
#include "EEPROM.h" 

#define relay 4
#define touch 12
#define ENERGY 1
#define DAC_RESOLUTION    (9)   // Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
Adafruit_MCP4725 dac;

#define RXD2 16
#define TXD2 17
String uart_message = "";

EnergyMonitor emon1;// Create an instance
EnergyMonitor emon2;
EnergyMonitor emon3;
#define current_transformer_1  32
#define current_transformer_2  33
#define current_transformer_3  25
float voltage = 0;

unsigned int touch_counter;
bool relay_flg = false;

/////////////////////ENERGY////////////////////////
float energy = 0 ;
float energy1 = 0.0;
float total_power = 0.0;
unsigned long e_last_time = 0;
unsigned long e_current_time = 0;
double total_amps;
bool energy_measure_flg = false;
unsigned char energy_read_delay;
////////////////////EEPROM /////////////////
unsigned int energy_address = 0;
unsigned int ener_stat_addr = 10;

//////////////////////////TIMER/////////////////////
unsigned int one_millisecond_counter;
unsigned char one_second_counter;
unsigned char hundred_ms_counter;
unsigned char one_minute_counter;
unsigned char epp_write_delay;
bool check_second;
hw_timer_t * timer = NULL;      //H/W timer defining (Pointer to the Structure)
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer();

void setup() {
  // put your setup code here, to run once:
  timer = timerBegin(1, 80, true);             // timer 0, prescalar: 80, UP counting
  timerAttachInterrupt(timer, &onTimer, true);   // Attach interrupt
  timerAlarmWrite(timer, 100, true);     // Match value= 1000000 for 1 sec. delay.
  timerAlarmEnable(timer);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.setTimeout(100);

  pinMode(relay, OUTPUT);
  pinMode(touch, INPUT);
  digitalWrite(relay, LOW);
  Serial.println("start");
  delay(1000);
  if (dac.begin(0x60))        //could be 0x60 or 0x62
  {
    Serial.println("MCP4725 Initialized Successfully.");
  }
  else
  {
    Serial.println("Failed to Initialize MCP4725.");
  }
  emon1.current(current_transformer_1, 5);
  emon2.current(current_transformer_2, 5);
  emon3.current(current_transformer_3, 4.9);

  if (!(EEPROM.begin(1000)))
  {
    Serial.println("E F");
  }
  default_set_eeprom_fun();
//  EEPROM.writeBool(ener_stat_addr, false);
//  EEPROM.commit();
  energy_measure_flg = EEPROM.readBool(ener_stat_addr);
  Serial.println("measure: " + String(energy_measure_flg));
  if(energy_measure_flg)
  energy1 = EEPROM.readFloat(energy_address);
  else
  energy1 = 0.00;
}

void loop()
{
 /* while ((digitalRead(touch)) && (touch_counter < 50))
  {
    touch_counter++;
    delay(100);
    Serial.println(String(touch_counter));
    if (touch_counter >= 40)
    {
      int current_state = digitalRead(relay);
      digitalWrite(relay, !current_state);
      break;
    }
  }
  touch_counter = 0;*/

  if (Serial2.available())
  {
    uart_message = "";
    uart_message = Serial2.readString();
    Serial.println("uart_message: " + uart_message);
    if ((uart_message[0] == '*') && (uart_message[4] == '#'))
    {
      Serial.println("substring: " + String(uart_message.substring(1, 4)));
      unsigned int check = (uart_message.substring(1, 4).toInt());

      Serial.println("check: " + String(check));
      voltage = 0.05 * check;
      if (check == 100)
      {
        voltage = 5.00;
      }
      Serial.println("voltage: " + String(voltage));
      dac.setVoltage((voltage * 4095.0) / 5.0, false);
      Serial2.print("*ok#");
    }
    else if ((uart_message == "pst") && (!energy_measure_flg)) //*pst#
    {
      energy_measure_flg = true;
      Serial.println("come into pst");
      energy1 = 0;
      EEPROM.writeBool(ener_stat_addr, true);
      EEPROM.writeFloat(energy_address, 000.00);
      EEPROM.commit();
      epp_write_delay = 1;
    }
    else if ((uart_message == "pct")/* && (energy_measure_flg)*/)
    {
      Serial.println("come into pct");
      sending_energy_fun();
      energy_measure_flg = false;
      EEPROM.writeBool(ener_stat_addr, false);
      EEPROM.writeFloat(energy_address, 000.00);
      energy1 = 0;
      EEPROM.commit();
      
    }
  }
  if ((energy_read_delay <= 0))
  {
    current_measurement_fun();
    energy_read_delay  = 1;
    Serial.println("energy_delay: " + String(energy_read_delay));
  }
}

void current_measurement_fun()
{
  double Irms_1 = emon1.calcIrms(1484);
  double Irms_2 = emon2.calcIrms(1484);
  double Irms_3 = emon3.calcIrms(1484);
  if (ENERGY)
  {
    Serial.println("irms_1: " + String(Irms_1));
    Serial.println("irms_2: " + String(Irms_2));
    Serial.println("irms_3: " + String(Irms_3));
  }
  Serial.println("energy_measure_done");
  total_amps = ((Irms_1 * 230) + (Irms_2 * 230) + ( Irms_3 * 230));
  total_power = total_amps;
  e_last_time = e_current_time;
  e_current_time = millis();
  energy = 0.0;
  energy = energy +  total_power * (( e_current_time - e_last_time) / 3600000.0) ; // calculate power in Watt-Hour // 1 Hour = 60mins x 60 Secs x 1000 Milli Secs
  energy1 = energy1 + (energy / 1000.00);
  Serial.println("energy_1: " + String(energy1));
  if ((epp_write_delay <= 0) && (energy_measure_flg))
  {
    EEPROM.writeFloat(energy_address, energy1);
    EEPROM.commit();
    Serial.println("energy1: " + String(energy1));
    epp_write_delay = 1;
    Serial.println("es");
  }
}

void default_set_eeprom_fun()
{
  if ((EEPROM.readBool(101)))
  {
    //epp_zero_fun();
    EEPROM.writeBool(101, false);
    EEPROM.writeBool(ener_stat_addr, false);
    EEPROM.writeFloat(energy_address, 000.00);
    EEPROM.commit();
    Serial.println("defaulting");
  }
}

void sending_energy_fun()
{
  Serial.println("energy1: " + String(energy1));
  if (energy1 < 10.00)
  {
    Serial.println("E0" + String(energy1, 2) + "#");
    Serial2.println("E0" + String(energy1, 2) + "#");
  }
  else if (energy1 < 100.00)
  {
    Serial.println("E" + String(energy1, 2) + "#");
    Serial2.println("E" + String(energy1, 2) + "#");
  }
  else if (energy1 < 1000.00)
  {
    Serial.println("E" + String(energy1, 1) + "#");
    Serial2.println("E" + String(energy1, 1) + "#");
  }
  else if (energy1 < 10000.00)
  {
    Serial.println("E0" + String(energy1, 0) + "#");
    Serial2.println("E0" + String(energy1, 0) + "#");
  }
  else if (energy1 < 100000.00)
  {
    Serial.println("E" + String(energy1, 0) + "#");
    Serial2.println("E" + String(energy1, 0) + "#");
  }
}
/////*pst# -- process start
/////*pct# -- process complete
/////@999.00# -- energy
