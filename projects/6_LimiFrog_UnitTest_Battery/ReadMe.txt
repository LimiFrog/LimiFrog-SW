BATTERY LEVEL MEASUREMENT TEST
==============================


Initialize Board

Set up ADC #3 to capture battery voltage on channel 2 in single shot mode.
Set up basic Timer6 to generate IT every 1s.

When Timer IT fires, enable voltage divider on Vbat and measure resulting voltage through ADC.
Display result. 

NOTE:
Voltage level vs remaining charge is not linear (and temperature dependent).
Fully charged LiPo battery supplies 4.1V-4.2V.
AS battery discharges, output voltage drops fairly quickly to a plateau between 3.8V and 3.6V. 
When output voltage reaches 3.4-3.6V, battery is almost fully discharged.
(If voltage drops too low, protection circuitry cuts off the cell as it is dangerous to discharge a LiPo below a certain level, e.g. 3V)
