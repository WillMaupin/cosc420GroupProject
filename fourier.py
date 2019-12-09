import numpy as np
from numpy import fft
from scipy.io import wavfile
import matplotlib.pyplot as plt

fs_rate, signal = wavfile.read("RubyMyDear.wav")

# convert stereo to mono
signal = signal.mean(axis=1)

# generate time in seconds
t = np.arange(signal.shape[0]) / fs_rate

# plot everything
#plt.plot(t, signal);

# create some plots
fig, axs = plt.subplots(
    2, sharex=True, sharey=True,
    figsize=(8, 6))

for ax, i in zip(axs, range(0, signal.shape[0], fs_rate)):
    # pull out sample for this second
    ss = signal[i:i + fs_rate]

    # generate FFT and frequencies
    sp = fft.fft(ss)
    freq = fft.fftfreq(len(ss), 1 / fs_rate)

    # plot the first few components
    ax.plot(freq[:2000], np.abs(sp.real[:2000]));

plt.show()
