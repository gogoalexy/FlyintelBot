import matplotlib.pyplot as plt
import numpy as np

inFile = open("MemPot21.dat","r") #open the FRates.dat file
#Number of total neurons: 61
t = []
N1 = []
N2 = []
N3 = []
N4 = []
N5 = []
N6 = []
N7 = []
N8 = []
N9 = []
N10 = []
N11 = []
N12 = []
N13 = []
N14 = []
N15 = []
N16 = []
N17 = []
N18 = []
N19 = []
N20 = []
N21 = []
N22 = []
N23 = []
N24 = []
N25 = []
N26 = []
N27 = []
N28 = []
N29 = []
N30 = []
N31 = []
N32 = []
N33 = []
N34 = []
N35 = []
N36 = []
N37 = []
N38 = []
N39 = []
N40 = []
N41 = []
N42 = []
N43 = []
N44 = []
N45 = []
N46 = []
N47 = []
N48 = []
N49 = []
N50 = []
N51 = []
N52 = []
N53 = []
N54 = []
N55 = []
N56 = []
N57 = []
N58 = []
N59 = []
N60 = []
N61 = []

FRates = inFile.readlines()

for line in FRates:
    tmp = line.split()
    t.append(tmp[0])
    N1.append(float(tmp[1]))
    N2.append(float(tmp[2]))
    N3.append(float(tmp[3]))
    N4.append(float(tmp[4]))
    N5.append(float(tmp[5]))
    N6.append(float(tmp[6]))
    N7.append(float(tmp[7]))
    N8.append(float(tmp[8]))
    N9.append(float(tmp[9]))
    N10.append(float(tmp[10]))
    N11.append(float(tmp[11]))
    N12.append(float(tmp[12]))
    N13.append(float(tmp[13]))
    N14.append(float(tmp[14]))
    N15.append(float(tmp[15]))
    N16.append(float(tmp[16]))
    N17.append(float(tmp[17]))
    N18.append(float(tmp[18]))
    N19.append(float(tmp[19]))
    N20.append(float(tmp[20]))
    N21.append(float(tmp[21]))
    N22.append(float(tmp[22]))
    N23.append(float(tmp[23]))
    N24.append(float(tmp[24]))
    N25.append(float(tmp[25]))
    N26.append(float(tmp[26]))
    N27.append(float(tmp[27]))
    N28.append(float(tmp[28]))
    N29.append(float(tmp[29]))
    N30.append(float(tmp[30]))
    N31.append(float(tmp[31]))
    N32.append(float(tmp[32]))
    N33.append(float(tmp[33]))
    N34.append(float(tmp[34]))
    N35.append(float(tmp[35]))
    N36.append(float(tmp[36]))
    N37.append(float(tmp[37]))
    N38.append(float(tmp[38]))
    N39.append(float(tmp[39]))
    N40.append(float(tmp[40]))
    N41.append(float(tmp[41]))
    N42.append(float(tmp[42]))
    N43.append(float(tmp[43]))
    N44.append(float(tmp[44]))
    N45.append(float(tmp[45]))
    N46.append(float(tmp[46]))
    N47.append(float(tmp[47]))
    N48.append(float(tmp[48]))
    N49.append(float(tmp[49]))
    N50.append(float(tmp[50]))
    N51.append(float(tmp[51]))
    N52.append(float(tmp[52]))
    N53.append(float(tmp[53]))
    N54.append(float(tmp[54]))
    N55.append(float(tmp[55]))
    N56.append(float(tmp[56]))
    N57.append(float(tmp[57]))
    N58.append(float(tmp[58]))
    N59.append(float(tmp[59]))
    N60.append(float(tmp[60]))
    N61.append(float(tmp[61]))
    
axis_font = {'size':'14'}

fig = plt.figure(1)
plt.xticks(np.arange(0, 1000, 0.5))
fig.text(0.08, 0.5, "Membrane Potential (V)", ha='center', va='center', rotation='vertical', **axis_font)
plt.subplot(411)
plt.plot(t, N6, 'r-')
plt.subplot(412)
plt.plot(t, N12, 'g-')
plt.subplot(413)
plt.plot(t, N18, 'b-')
plt.subplot(414)
plt.plot(t, N24, 'y-')
plt.xlabel("Time (s)", **axis_font)

inFile.close()
plt.show()
