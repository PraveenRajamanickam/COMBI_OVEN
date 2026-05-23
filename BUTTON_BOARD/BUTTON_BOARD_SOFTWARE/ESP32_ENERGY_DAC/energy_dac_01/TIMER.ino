void IRAM_ATTR onTimer() {      //Defining Inerrupt function with IRAM_ATTR for faster access
  portENTER_CRITICAL_ISR(&timerMux);
  if (++one_millisecond_counter >= 10)
  {
    one_millisecond_counter = 0;

    if (++hundred_ms_counter >= 100)
    {
      hundred_ms_counter = 0;

      if (++one_second_counter >= 10)
      {
        one_second_counter = 0;
        if(energy_read_delay>0)
        energy_read_delay--;
        if (++one_minute_counter >= 60)
        {
          one_minute_counter = 0;
          if(epp_write_delay>0)
          epp_write_delay--;
        }
      }
    }
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}
