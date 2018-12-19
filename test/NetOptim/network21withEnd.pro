EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc1
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc4
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc7
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc10
GaussMean=0.0
GaussSTD=0.1
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc2
GaussMean=0.45
GaussSTD=0.05
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc3
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc5
GaussMean=0.45
GaussSTD=0.05
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc6
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc8
GaussMean=0.45
GaussSTD=0.05
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc9
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc11
GaussMean=0.45
GaussSTD=0.05
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc12
GaussMean=0.23
GaussSTD=0.07
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc20
GaussMean=0.25
GaussSTD=0.1
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc21
GaussMean=0.25
GaussSTD=0.1
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc22
GaussMean=0.25
GaussSTD=0.1
EndEvent

EventTime 10.0
Type=ChangeMembraneNoise
Label=#1#
Population: Exc23
GaussMean=0.25
GaussSTD=0.1
EndEvent

%fixed random input
EventTime 100.0
Type=ChangeExtFreq
Label=#1#
Population: Exc20
Receptor: AMPA
FreqExt=2000
EndEvent

EventTime 100.0
Type=ChangeExtFreq
Label=#1#
Population: Exc21
Receptor: AMPA
FreqExt=2000
EndEvent

EventTime 100.0
Type=ChangeExtFreq
Label=#1#
Population: Exc22
Receptor: AMPA
FreqExt=2000
EndEvent

EventTime 100.0
Type=ChangeExtFreq
Label=#1#
Population: Exc23
Receptor: AMPA
FreqExt=2000
EndEvent

EventTime 1000.0
Type=ChangeExtFreq
Label=#1#
Population: Exc1
Receptor: AMPA
FreqExt=4000
EndEvent

EventTime 5000.0
Type=ChangeExtFreq
Label=#1#
Population: Exc1
Receptor: AMPA
FreqExt=0
EndEvent

EventTime 10000.0
Type=EndTrial
Label=End_of_the_trial
EndEvent

%--------------------------------------------------------------------

OutControl

FileName:MemPot21.dat
Type=MemPot
population: AllPopulation
EndOutputFile

FileName:Spikes21.dat
Type=Spike
population: AllPopulation
EndOutputFile

FileName:FRates21.dat
Type=FiringRate
FiringRateWindow=50
PrintStep=50
population: AllPopulation
EndOutputFile

EndOutControl
