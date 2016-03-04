COMPOSITE DEMO OF VARIOUS FEATURES OF THE LIMIFROG MODULE
=========================================================



1) Step1: 
Splash Screen = LimiFrog Logo
   = Decode image SPLASH.SPE (.SPE for image with a Special role...) which is actually a BMP file

“Free” the frog by putting hand in front of VL6180X detecttor
Frog can then be moved by tilting LimiFrog
(challenge: try to keep it centered !)

Then next step of demo is triggered by Microphone noise detection :
lightly tap on the bottom right corner of LimiFrog (just below the screen)
...or clap your hands
...or “click” your tongue

2) Step2: 
Carroussel of pictures

Select previous or next picture by tilting LimiFrog
Stop on current picture by keeping LimiFrog horizontal

First picture displayed is always bitmap picture FROG.SPE (which has to be on the file system).
Then all.BMP files found at the root of the file system are cycled through.

	<Next step: light tap or noise>

3) Step3: 
Real-time display of graph with accelerometer XYZ axis values
(similar to Demo_Accel_Viz_TimeDomain)

	<Next step: light tap or noise>

4) Step 4 : Time-domain and FFT display of magnetomer values
- Capture sequence of magnetomer values,
at fairly slow rate (20Hz) so user can modify orientation at speed meaningful vs capture rate
- At the end of sequence, display FFT of values captured on Z axis
==> if user swings LimiFrog around Z-axis regularly during capture, swing frequency shows up on
FFT
Note: uncalibrated magnetometer values are used. Not an issue here as only affects DC Value of FFT.
(similar to Demo_Magnetometer_Viz_FFT) 

	<Next step: light tap or noise>

5) Step 5: VL6180X demo
Detects distance of hand or object up to 20cm
(similar to Demo_ProxDist_VL6180X)

	<Next step: light tap or noise>

6) Step 6: LPS25H demo
Display measured atmospheric pressure
(similar to Demo_DisplayPressure)

	<Next step: light tap or noise>

Then Back to start (Splash Screen)



