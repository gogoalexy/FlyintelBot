import matplotlib.pyplot as plt
import numpy as np

inFile = open("Spikes20.dat","r") #open the Spikes.dat file
t = []
spike = []

FRates = inFile.readlines()

for line in FRates:
    tmp = line.split()
    t.append(tmp[0])
    spike.append(tmp[1])
    
axis_font = {'size':'14'}

fig = plt.figure(1)
plt.xticks(np.arange(0, 1000, 0.5))
plt.plot(t, spike, 'k.')
plt.xlabel("Time (s)", **axis_font)

inFile.close()
plt.show()
