#ifndef MONITOR_H

#include <vector>
#include "net_struct_def.h"
#include "max7219.h"
//#include "flyintel.h"??


class NeuroMonitor {
public:
	NeuroMonitor();
	int sortinghat(); //friend of flyintel
	int visualize(NetStruct);
	void refresh();

private:
	int state;

};

#define MONITOR_H
#endif
