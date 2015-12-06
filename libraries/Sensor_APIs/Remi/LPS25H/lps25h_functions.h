#pragma once

void lps25h_init(unsigned char deviceAddress);
void lps25h_i2c_init(void);
void lps25h_initialization(void);
float lps25h_get_temperature();
float lps25h_get_pressure();

