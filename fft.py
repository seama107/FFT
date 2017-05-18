# %%
import numpy as np
import matplotlib.pyplot as plt
import timeit
import time

# %%

def DFT_verbose(x):
    n = len(x)
    y = np.zeros(n, dtype=complex)
    omega = np.cos(np.pi * 2 / n) + 1j * np.sin(np.pi * 2 / n)
    for i in range(n):
        for k in range(n):
            y[i] += x[k]*omega**(i*k)
    return y

def DFT_slow(x):
    """Computes the discrete Fourier Transform of the 1D array x using matrix/vector dot"""
    x = np.asarray(x, dtype=complex)
    N = x.shape[0]
    k = np.arange(N)
    l = k.reshape((N, 1))
    F = np.cos(-2* np.pi * k * l / N) + 1j * np.sin(-2* np.pi * k * l / N)
    return np.dot(F, x)

def FFT(x):
    """Recursive implementation of the 1D Cooley-Tukey FFT"""
    x = np.asarray(x, dtype=complex)
    N = x.shape[0]
    if N % 2 > 0:
        raise ValueError("size of x must be power of 2")
    elif N <= 16:
        return DFT_slow(x)
    else:
        X_even = FFT(x[::2])
        X_odd = FFT(x[1::2])
        factor = np.cos(-2* np.pi * np.arange(N) / N) + 1j * np.sin(-2* np.pi * np.arange(N) / N)
        return np.concatenate([ X_even + factor[:N//2] * X_odd, X_even + factor[N//2:] * X_odd ])



def plot_diff_between_functions(t, x1, x2, title="x_2(t) - x_1(t)", xaxis="t", yaxis="x"):
    plot_func(t, x2-x1, title, xaxis, yaxis)

def plot_func(t, x, title, xaxis, yaxis):
    plt.plot(t, x)
    plt.title(title)
    plt.xlabel(xaxis)
    plt.ylabel(yaxis)
    plt.show()

def plot_spec_density(X):
    X = np.asarray(X, dtype=complex)
    n = X.shape[0]
    amps = np.fft.fftshift(X)
    spec_dens = np.square(np.absolute(amps))
    freqs = np.linspace(-1 * n/4, n/4, n)
    plot_func(freqs, spec_dens, "Spectral density of x", '$f$', 'A')


# %%

inputSizes = pow(2, np.arange(0, 12) + 6)

fft_time = np.zeros(12)

for i in range(len(inputSizes)):
    n = inputSizes[i];
    t = np.linspace(0, 4*np.pi, n)
    x = np.sin(t) + np.sin(3*t) + .4 * np.sin(7 * t)
    fft_time[i] = timeit.timeit('FFT(x)', setup='import numpy as np\nfrom __main__ import FFT\nn=%d \nt = np.linspace(0, 4*np.pi, n)\nx = np.sin(t) + np.sin(3*t) + .4 * np.sin(7 * t)'%n, number = 10) / 10.0
plt.close()
plt.plot(np.log2(inputSizes), fft_time)
plt.title("Computation time for FFT")
plt.xlabel("$\log_2{n}$")
plt.ylabel("Computation time (s)")
plt.savefig("fftTime.png")

sampleRate = 128
n = 2**10
t_max = (n-1)/sampleRate
t = np.linspace(0, t_max, n, dtype=complex)
delta_t = np.diff(t)[0]
x = np.sin(t * 2 * np.pi ) + np.sin(3*t * 2 * np.pi) + .4 * np.sin(7 * t* 2 * np.pi)
X = np.fft.fft(x)
amps = np.fft.fftshift(X)
spec_dens = np.square(np.absolute(amps))
freqs = np.linspace(-1 * n/4, n/4, n)

# %%
plt.close()
fig, (ax1, ax2) = plt.subplots(2)

ax1.plot(t, x)
ax1.set_title('f(t) for $\delta t = %f$' % delta_t)
ax1.set_xlabel('t')
ax1.set_ylabel('x')

ax2.plot(freqs, spec_dens)
#ax2.plot(freqs, spec_dens2)
ax2.set_title('Spec. dens.')
ax2.set_xlabel('$\omega$')
ax2.set_xbound([-30, 30])
ax2.set_ylabel('$|A|^2$')

fig.subplots_adjust(hspace = .6)
plt.savefig('plot.png')
