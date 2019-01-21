#include "monitor.h"

using namespace std;

NeuroMonitor::NeuroMonitor()
{
	neurogroup = {0};
}

struct Container NeuroMonitor::sortinghat(int max)
{
	for(int i=2; i<max; i+=3){
		int tmp = spiketrain[i];
		if(tmp > 40)
		{
			continue;
		}
		else if(tmp > 25)
		{
			switch(tmp)
			{
				case 26 ... 27:
					neurogroup.rsensorF++;
					continue;
				case 28 ... 30:
					neurogroup.FInh++;
					continue;
				case 31 ... 32:
					neurogroup.rsensorBL++;
					continue;
				case 33 ... 35:
					neurogroup.BLInh++;
					continue;
				case 36 ... 37:
					neurogroup.rsensorBR++;
					continue;
				case 38 ... 40:
					neurogroup.BRInh++;
					continue;
			}
		}
		else if(tmp == 24 || tmp == 25)
		{
			neurogroup.globalInh++;
		}
		else if(tmp >= 18)
		{
			switch(tmp)
			{
				case 18 ... 19:
					neurogroup.fsensorR++;
					continue;
				case 20 ... 22:
					neurogroup.pmR++;
					continue;
				case 23:
					neurogroup.motorR++;
					continue;
			}
		}
		else if(tmp >= 12)
		{
			switch(tmp)
			{
				case 12 ... 13:
					neurogroup.fsensorL++;
					continue;
				case 14 ... 16:
					neurogroup.pmL++;
					continue;
				case 17:
					neurogroup.motorL++;
					continue;
			}
		}
		else if(tmp >= 6)
		{
			switch(tmp)
			{
				case 6 ... 7:
					neurogroup.fsensorB++;
					continue;
				case 8 ... 10:
					neurogroup.pmB++;
					continue;
				case 11:
					neurogroup.motorB++;
					continue;
			}
		}
		else if(tmp >= 0)
		{
			switch(tmp)
			{
				case 0 ... 1:
					neurogroup.fsensorF++;
					continue;
				case 2 ... 4:
					neurogroup.pmF++;
					continue;
				case 5:
					neurogroup.motorF++;
					continue;
			}
		}
	}

	struct Container motorOut{motorF, motorB, motorL, motorR};
	return motorOut;
}

int NeuroMonitor::visualize(struct NeuroCatalog neurogroup)
{
	if(neurogroup.rsensorF)
	{
		registerWrite(CATHODE_FUNC(ROW.rsensorF), ANODE_FUNC(COL.rsensorF));
	}
	if(neurogroup.rsensorBL)
	{
		registerWrite(CATHODE_FUNC(ROW.rsensorBL), ANODE_FUNC(COL.rsensorBL));
	}
	if(neurogroup.rsensorBR)
	{
		registerWrite(CATHODE_FUNC(ROW.rsensorBR), ANODE_FUNC(COL.rsensorBR));
	}
	
	if(neurogroup.fsensorF)
	{
		registerWrite(CATHODE_FUNC(ROW.fsensorF), ANODE_FUNC(COL.fsensorF));
	}
	if(neurogroup.fsensorB)
	{
		registerWrite(CATHODE_FUNC(ROW.fsensorB), ANODE_FUNC(COL.fsensorB));
	}
	if(neurogroup.fsensorL)
	{
		registerWrite(CATHODE_FUNC(ROW.fsensorL), ANODE_FUNC(COL.fsensorL));
	}
	if(neurogroup.fsensorR)
	{
		registerWrite(CATHODE_FUNC(ROW.fsensorR), ANODE_FUNC(COL.fsensorR));
	}
	
	if(neurogroup.pmF)
	{
		registerWrite(CATHODE_FUNC(ROW.pmF), ANODE_FUNC(COL.pmF));
	}
	if(neurogroup.pmB)
	{
		registerWrite(CATHODE_FUNC(ROW.pmB), ANODE_FUNC(COL.pmB));
	}
	if(neurogroup.pmL)
	{
		registerWrite(CATHODE_FUNC(ROW.pmL), ANODE_FUNC(COL.pmL));
	}
	if(neurogroup.pmR)
	{
		registerWrite(CATHODE_FUNC(ROW.pmR), ANODE_FUNC(COL.pmR));
	}
	
	if(neurogroup.FInh)
	{
		registerWrite(CATHODE_FUNC(ROW.FInh), ANODE_FUNC(COL.FInh));
	}
	if(neurogroup.BLInh)
	{
		registerWrite(CATHODE_FUNC(ROW.BLInh), ANODE_FUNC(COL.BLInh));
	}
	if(neurogroup.BRInh)
	{
		registerWrite(CATHODE_FUNC(ROW.BRInh), ANODE_FUNC(COL.BRInh));
	}
	if(neurogroup.globalInh)
	{
		registerWrite(CATHODE_FUNC(), ANODE_FUNC(COL.globalInh));
	}
	
	if(neurogroup.motorF)
	{
		registerWrite(CATHODE_FUNC(ROW.motorF), ANODE_FUNC(COL.motorF));
	}
	if(neurogroup.motorB)
	{
		registerWrite(CATHODE_FUNC(ROW.motorB), ANODE_FUNC(COL.motorB));
	}
	if(neurogroup.motorL)
	{
		registerWrite(CATHODE_FUNC(ROW.motorL), ANODE_FUNC(COL.motorL));
	}
	if(neurogroup.motorR)
	{
		registerWrite(CATHODE_FUNC(ROW.motorR), ANODE_FUNC(COL.motorR));
	}
}



void NeuroMonitor::refresh()
{
	neurogroup = {0};
	matrix_clear();
}
