import matplotlib.pyplot as plt
import numpy as np

inFile = open("FRates20.dat","r") #open the FRates.dat file
t = []
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
Inh13 = []
Exc14 = []
Inh15 = []
Exc16 = []
Inh17 = []
Exc18 = []
Inh19 = []
Exc20 = []
Exc21 = []
Exc22 = []
Exc23 = []
Exc24 = []
Exc25 = []
Exc26 = []
Exc27 = []

FRates = inFile.readlines()

for line in FRates:
    tmp = line.split()
    t.append(tmp[0])
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
    Inh13.append(float(tmp[13]))
    Exc14.append(float(tmp[14]))
    Inh15.append(float(tmp[15]))
    Exc16.append(float(tmp[16]))
    Inh17.append(float(tmp[17]))
    Exc18.append(float(tmp[18]))
    Inh19.append(float(tmp[19]))
    Exc20.append(float(tmp[20]))
    Exc21.append(float(tmp[21]))
    Exc22.append(float(tmp[22]))
    Exc23.append(float(tmp[23]))
    Exc24.append(float(tmp[24]))
    Exc25.append(float(tmp[25]))
    Exc26.append(float(tmp[26]))
    Exc27.append(float(tmp[27]))
    
axis_font = {'size':'14'}

fig = plt.figure(1)
plt.xticks(np.arange(0, 1000, 0.5))
fig.text(0.08, 0.5, "Firing Rates (Hz)", ha='center', va='center', rotation='vertical', **axis_font)
plt.subplot(411)
plt.plot(t, Exc3, 'r-')
plt.subplot(412)
plt.plot(t, Exc6, 'g-')
plt.subplot(413)
plt.plot(t, Exc9, 'b-')
plt.subplot(414)
plt.plot(t, Exc12, 'y-')
plt.xlabel("Time (s)", **axis_font)

inFile.close()
plt.show()
