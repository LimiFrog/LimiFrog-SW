LIS3MDL Magnetometer Demo
=========================

Calibrate Magnetometer with user intervention
Display North continuously
Demo to run with LimiFrog laying flat (as Z axis not taken into account in this demo)

Note:
LIS3MDL is supposed to be calibrated in factory for zero-gauss offset.
However I see a significant offset (equivalent to soft-iron effect) -- perhaps because the factory calibration is done at 2.5V (cf datasheet) and LimiFrog uses 3V.
So demo starts with a calibration in XY plane(Z ignored, demo assumed to be with LimiFrog laying flat):  measure average X coordinate and average Y coordinate over 8 equally spaced orientations (angles) the theoretical is zero, the actual result is an offset to cancel.
