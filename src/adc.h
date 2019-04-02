#ifndef ADC_H

class ADC
{
public:
    virtual bool isInit()
    {
        return false;
    }
    virtual int whichPin()
    {
        return 0;
    }
    virtual int readChan()
    {
        return -1;
    }
    virtual void writeChan()
    {
        return;
    }

protected:
    bool isInit;
};

#define ADC_H
#endif
