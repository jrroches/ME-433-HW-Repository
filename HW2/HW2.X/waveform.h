#ifndef WAVEFORM__H__
#define WAVEFORM__H__

void test_waveform ();
void delay_ms(unsigned int t);
void output_waveform (char channel, unsigned short waveform_value);
void generate_triangle_wave (unsigned short arr[]);
void generate_sine_wave (unsigned short arr[]);

#endif // WAVEFORM__H__