import numpy as np
import scipy.fft as fft
import matplotlib.pyplot as plt

fs = 1000
t = np.arange(0, 1, 1/fs)
N = len(t)
f = 10
y = 3* np.sin(2*np.pi*f*t)

y_fft= abs(fft.fft(y))/ N
f_fft = fft.fftfreq(len(t), 1/fs)
plt.figure(1)
plt.plot(t, y)

plt.figure(2)
plt.plot(f_fft, y_fft)

plt.show()
