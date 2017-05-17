# %%
import numpy as np
import matplotlib.pyplot as plt

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

n = 3 * 256
t = np.linspace(0, 4*np.pi, n)
delta_t = np.diff(t)[0]
x = np.sin(t) + np.sin(3*t) + .4 * np.sin(7 * t)
#x = np.random.rand(n+1) - .5

X0 = np.fft.fft(x)
X1 = DFT_slow(x)
X2 = FFT(x)

plot_spec_density(X0)
plot_spec_density(X1)


#plot_diff_between_functions(freqs, amps1, amps2, title="Diff between FTs", xaxis="$\omega$", yaxis="A")


#omega_max = np.absolute( freqs[ np.argmax(spec_dens)])
#freqs_subset = freqs[n//2 - 50: n//2 + 50] if n > 100 else freqs
#spec_dens_subset = spec_dens[n//2 - 50: n//2 + 50] if n > 100 else spec_dens





# %%
fig, (ax1, ax2) = plt.subplots(2)

ax1.plot(t, x)
ax1.set_title('sin(t) for $\delta t = %f$' % delta_t)
ax1.set_xlabel('t')
ax1.set_ylabel('x')

ax2.plot(freqs, spec_dens1)
#ax2.plot(freqs, spec_dens2)
ax2.set_title('Spec. dens.')
ax2.set_xlabel('$\omega$')
ax2.set_ylabel('$|A|^2$')

fig.subplots_adjust(hspace = .6)
plt.show()
