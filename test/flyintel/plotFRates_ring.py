import matplotlib.pyplot as plt
import numpy as np

inFile = open("Flyintel.log","r") #open the FRates.dat file
Exc0 = []
Exc1 = []
Exc2 = []
Exc3 = []
Exc4 = []
Exc5 = []
Exc6 = []
Exc7 = []
Exc8 = []
Exc9 = []
Exc10 = []
Exc11 = []
Exc12 = []
Exc13 = []
Exc14 = []
Exc15 = []


FRates = inFile.readlines()

for line in FRates:
    tmp = line.split()
    Exc0.append(float(tmp[0]))
    Exc1.append(float(tmp[1]))
    Exc2.append(float(tmp[2]))
    Exc3.append(float(tmp[3]))
    Exc4.append(float(tmp[4]))
    Exc5.append(float(tmp[5]))
    Exc6.append(float(tmp[6]))
    Exc7.append(float(tmp[7]))
    Exc8.append(float(tmp[8]))
    Exc9.append(float(tmp[9]))
    Exc10.append(float(tmp[10]))
    Exc11.append(float(tmp[11]))
    Exc12.append(float(tmp[12]))
    Exc13.append(float(tmp[13]))
    Exc14.append(float(tmp[14]))
    Exc15.append(float(tmp[15]))
    

ring = np.array([Exc0, Exc1, Exc2, Exc3, Exc4, Exc5, Exc6, Exc7, Exc8, Exc9, Exc10, Exc11, Exc12, Exc13, Exc14, Exc15])
ring = np.transpose(ring)
axis_font = {'size':'14'}

fig = plt.figure()
plt.imshow(ring, cmap='OrRd', aspect=0.08, interpolation='nearest', origin='upper')
#plt.xticks(np.arange(0, 1000, 0.5))
#fig.text(0.08, 0.5, "Firing Rates (Hz)", ha='center', va='center', rotation='vertical', **axis_font)
#plt.xlabel("Time (s)", **axis_font)

inFile.close()
plt.show()
