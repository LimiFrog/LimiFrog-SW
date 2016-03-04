Demo_PressureTemp_NoiseLevel
===========================

USB active

Configure ADC channel connected to Microphone output
to trigger IT upon noise level exceeding a threshold
(using analog watchdog functionality of ADC).

Display measured atmospheric pressure and ambiant temperature
measured by LPS25H.

Update every second.

Background color toggles (between orange gradient and blue gradient) when noise pciked by microphone exceeds a certain threshold
--> clap your hands or "click" your tongue or your finges
    ...or tap lightly the case around microphone location

Note: 
====
Temperature is measured at board level, so heat from board,
possibly confined (e.g. if board is stacked and/or in case),
will cause a small temperature rise.


