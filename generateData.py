# %%
import numpy as np

'''
Prints out data for a wave form to a file. File format is as follows
line 1: the number of data points
line 2: the sample rate in Hz
line 2+: data
'''

sampleRate = 48000
n = 2**10
t_max = (n-1)/sampleRate
t = np.linspace(0, t_max, n, dtype=complex)
delta_t = np.diff(t)[0]
x = np.sin(t * 2 * np.pi ) + np.sin(3*t * 2 * np.pi) + .4 * np.sin(7 * t* 2 * np.pi)

f = open('sigDataSmall.txt', 'a')
f.write(str(n) + '\n')
f.write(str(sampleRate))
f.write('s\n')
for v in x:
    f.write( '(%.8f,%.8f)\n' % (v.real, v.imag) )
f.close()
