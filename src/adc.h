#ifndef ADC_H

class ADC
{
public:
    ADC() : init(false)
    {}
    virtual bool isInit()
    {
        return false;
    }
    virtual int whichPin()
    {
        return 0;
    }
    virtual int readChan(int pin)
    {
        return -1;
    }
    virtual void writeChan(int pin, int value)
    {
        return;
    }

protected:
    bool init;
};

#define ADC_H
#endif
