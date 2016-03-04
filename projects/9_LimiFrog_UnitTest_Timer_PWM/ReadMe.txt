TIMERS AND PWM
===============

Part 1: Free running timer 

Based on timer3 counter monitoring,
Flash LED every 0.5s, 8 times, using timer with 1ms resolution.
Short pause.
Do it again using timer with 1us resolution (same result !)


Part 2: Timer with IT generation.

Set up timer4 to elapse after 0.1s and generate IT .
In Interrupt Servic Routine, toggle LED.
Let it run for a few seconds.
During that time: LED is blinking, toggling every 100ms (so fqcy = 5Hz)


Part 3: PWM.


Set up PWM on extension port position 11 which can bear channel 4 of timer 4: with 100ms period and 3 selectable pulse periods for 25%, 50% and 75% duty cycle -- side push-button switch allows to change the selection.
Program LED to follow logic level present on PWM output.

