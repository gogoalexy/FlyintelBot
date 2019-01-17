#ifndef MONITOR_H

#include "max7219.h"
//#include "flyintel.h"??


struct NeuroCatalog {
	short fsensorF;
	short fsensorB;
	short fsensorL;
	short fsensorR;
	short rsensorF;
	short rsensorBL;
	short rsensorBR;
	short pmF;
	short pmB;
	short pmL;
	short pmR;
	short globalInh;
	short FInh;
	short BLInh;
	short BRInh;
	short motorF;
	short motorB;
	short motorL;
	short motorR;
}

class NeuroMonitor {
public:
	NeuroMonitor();
	int sortinghat(); //friend of flyintel
	int visualize();
	void refresh();

private:
	struct NeuroCatalog neurogroup;
	enum ROW { fsensorF = 0, fsensorL = 5, fsensorB = 7, fsensorR = 4,
		rsensorF = 0, rsensorBL = 7, rsensorBR = 7,
		pmF = 1, pmB = 6, pmL = 4, pmR = 3,
		globalInh = 4, FInh = 1, BLInh = 6, BRInh = 6,
		motorF = 0, motorB = 7, motorL = 4, motorR = 3 };
	enum COL { fsensorF = 2, fsensorL = 0, fsensorB = 3, fsensorR = 7,
		rsensorF = 4, rsensorBL = 0, rsensorBR = 7,
		pmF = 3, pmB = 4, pmL = 1, pmR = 6,
		globalInh = 3, FInh = 4, BLInh = 1, BRInh = 6,
		motorF = 3, motorB = 4, motorL = 0, motorR = 7 };

};

#define MONITOR_H
#endif
