MICROPHONE and ADC TEST (in analog watchdog mode)
===============================================

Initialize Board

Set Up ADC#2 to capture Microphone analog output on channel 15.
Set up basic Timer6 at 20KHz as trigger for ADC sampling.
Set up analog watchdog to detect ADC input goes outside a target window.

When noise level exceeds a certain level, analog watchdog detect it and sets a flag (could also fire IT but not used here).

Color of screen is toggled and LED is flashed upon detection of this flag.

Demo by e.g  clapping hands near LimiFrog.


