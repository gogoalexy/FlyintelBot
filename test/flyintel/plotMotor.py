import matplotlib.pyplot as plt
import numpy as np

inFile = open("Speed.log","r") #open the Spikes.dat file
t = []
vL = []
vR = []
cmd = []
loop = 0

Motors = inFile.readlines()

for line in Motors:
	loop = loop+1
	tmp = line.split()
	t.append(int(tmp[0]))
	vL.append(int(tmp[1]))
	vR.append(int(tmp[2]))
	cmd.append(tmp[3])
	if loop > 200:
		break


loop = 0
axis_font = {'size':'14'}

fig,ax = plt.subplots(1)
#plt.xticks(np.arange(0, 1000, 0.5))
plt.plot(t, vL, 'k.-', t, vR, 'b.-')
for direction in cmd:
	loop = loop+1
	if direction == 'F':
		ax.axvspan(loop, loop+1, facecolor='r', alpha=0.5)
	elif direction == 'B':
		ax.axvspan(loop, loop+1, facecolor='g', alpha=0.5)
	elif direction == 'L':
		ax.axvspan(loop, loop+1, facecolor='c', alpha=0.5)
	elif direction == 'R':
		ax.axvspan(loop, loop+1, facecolor='y', alpha=0.5)

plt.xlabel("Iteration", **axis_font)
plt.ylabel("Motor Strength", **axis_font)

inFile.close()
plt.show()
