#ifndef MONITOR_H

#include <vector>
#include "net_struct_def.h"
#include "max7219.h"
//#include "flyintel.h"??


class NeuroMonitor
{
public:
	NeuroMonitor();
	int init(int, int);
	int sortinghat(); //friend of flyintel
	void registerWrite(int, unsigned char, unsigned char);
	int visualize(NetStruct);
	void refresh();
	
	inline unsigned char CATHODE_FUNC(int position)
    {
        return 0x01 + position;
    }

    inline unsigned char ANODE_FUNC(int position)
    {
        return 0x80 >> position;
    }

    inline unsigned int GLUE(unsigned char addr1, unsigned char addr2)
    {
        return addr1 | addr2 << 8;
    } 

private:
	int state;
};

#define MONITOR_H
#endif
