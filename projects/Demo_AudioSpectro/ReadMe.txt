TIME DOMAIN AND FFT VISUALISATION OF AUDIO DATA FROM MEMS MICROPHONE
=================================================================================


// =================================================================
// IMPORTANT NOTES:
//
// 1) In this demo,the user is expected to provide an EXTERNAL 
// CONNECTION between the microphone output on Extension Port
// Position 1 and the PGA (Programmable Gain Amplifier) input
// on Extension Port Position 8
//
// 2) This demo amplifies the microphone output with PGA, as the 
// microphone signal is weak.
// Microphone output is biased at VCC/2 ~ 1.5V, keeping it at that
// level leads to ADC saturation (ADC range = 0-3V)
// Therefore it is required to lower the mic output DC biasing,
// which can be done by CONNECTING AN EXTERNAL RESISTOR between
// mic output on Extension Port Position 1 and GND (e.g. on
// Extension Port Position 9).
// As the biasing is done on the board by a 47K+47K resistor bridge,
// connecting e.g. an external 1K resistor brings the biasing voltage
// down to ~ 60mV. With the audio signal less than 120mV peak-to-peak 
// in most situations this is OK. Pick a larger resistor for higher
// DC bias
//
// =================================================================


At beginning of demo, user can select time-domain or frequency domain

Program captures audio samples at 8KHz sample rate.
> If time-domain selected: show in time-domain the 128 audio samples that can be used for FFT, after optional FFT-optimized windowing (Hamming)
> If FFT-domain selected: show the FFT of the signal between 0 and Fs/2 = 4KHz

Note - Try whistling at different pitch height and volume to see the effect


