
1) HLE handles:
- UI updates, error reporting
- Reading UI settings, do not allow charging parameters to change via UI while charging
- Saving charging parameters to NVM
- Reading charging parameters from NVM
- Reading temperature, adjusting target current, air flow control
- Stop and start charging
- If battery charging state machine returns any error except Reverse Polarity
  HLE stops charging and waits for battery to be disconnected.
  
2) Battery charging state machine handles:
- Progression through charging algorithm
- Controlling output, voltage, current
- Battery charging error detection
- Restart after Reverse Polarity cleared

3) Port Layer functions
- uint16_t ReadBatteryVoltage_mV(void)
  Reads the ADC for the external battery voltage, converts to milli-Volts and adjusts for calibration

- uint16_t ReadIntBatteryVoltage_mV(void)
  Reads the ADC for the internal battery voltage, converts to milli-Volts and adjusts for calibration
  
- uint16_t ReadOutputCurrent_mA(void)
  Reads the ADC for the current flow to the external battery, converts to milli-Amps and adjusts for calibration
  
- int SetOutputVoltage_mV(unint16 outputmV)
  Sets the commanded output voltage via HW adjusting for calibration.  Returns 0 if succsess, -1 otherwise.
  
- int SetOutputCurrent_mA(uint16 ouptutmA)
  Sets the commanded output current via HW adjusting for calibration.  Returns 0 if succsess, -1 otherwise

- int EnabledOutput(void)
  Closes the output path to the battery clamps via HW
  
- int DisableOutput(void)
  Opens the output path to the battery clamps via HW

- int IsPolarityReversed(void)
  Reads the HW reverse polarity detection.  Returns 1 if polarity is reversed.

- uint32 GetTime_seconds(void)
  Reads HW clock/timer free running timer, converts to seconds.
  Algorithm uses differential time.
  
- void Delay_milliseconds(uint16 delay_milliSec)
  Call system/OS level delay for the requested number of milliseconds.
  
