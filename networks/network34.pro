EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:FS1
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:FS2
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:FS3
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:FS4
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:TS1
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:TS2
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:TS3
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:TS4
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Pm1
GaussMean=0.05
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Pm2
GaussMean=0.05
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Pm3
GaussMean=0.05
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Pm4
GaussMean=0.05
GaussSTD=0.1
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:rPm1
GaussMean=0.05
GaussSTD=0.15
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:rPm2
GaussMean=0.05
GaussSTD=0.15
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:rPm3
GaussMean=0.05
GaussSTD=0.15
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:rPm4
GaussMean=0.05
GaussSTD=0.15
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:M1
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:M2
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:M3
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:M4
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Inh1
GaussMean=0.05
GaussSTD=0.05
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Inh2
GaussMean=0.05
GaussSTD=0.05
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Inh3
GaussMean=0.05
GaussSTD=0.05
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:Inh4
GaussMean=0.05
GaussSTD=0.05
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:GInh
GaussMean=0.05
GaussSTD=0.05
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:random1
GaussMean=1.0
GaussSTD=0.8
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:random2
GaussMean=1.0
GaussSTD=0.8
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:random3
GaussMean=1.0
GaussSTD=0.8
EndEvent

EventTime 0.0
Type=ChangeMembraneNoise
Label=#1#
Population:random4
GaussMean=1.0
GaussSTD=0.8
EndEvent

%------------------------------------------------

OutControl

FileName:FRates.dat
Type=FiringRate
FiringRateWindow=50
PrintStep=50
population:AllPopulation
EndOutputFile

FileName:MemPot.dat
Type=MemPot
population:AllPopulation
EndOutputFile

FileName:Spikes.dat
Type=Spike
population:AllPopulation
EndOutputFile

EndOutControl
