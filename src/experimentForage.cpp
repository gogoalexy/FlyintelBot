#include <iostream>
#include <fstream>
#include <array>
#include "connect_to_flysim.h"
#include "spikesHandler.h"
#include "flyintel.h"
#include "timer.h"
#ifdef PI
    #include <wiringPi.h>
    #include "adc.h"
    #include "SPIadc.h"
    #include "Sharp_IR.h"
    #include "pixycam.h"
    #include "DCmotor.h"
#endif

using namespace std;

char *Spikes = nullptr;

enum Actions{Stop, Forward, Backward, Left, Right};
enum TargetLocation{NA = -1, CL = 15, CC = 0, CR = 1};

const bool CUTOFF_PIXY = FALSE;

int main()
{
    cout<<"========================================"<<'\n'
        <<"[        Initializing Flyintel ...     ]"<<'\n'
        <<"========================================"<<endl;

    #ifdef PI
        //wiringPi init in BCM pinout
        wiringPiSetupGpio();
        pinMode(16, OUTPUT); //yellow LED
        pinMode(20, OUTPUT);
        digitalWrite(16, LOW);
        digitalWrite(20, LOW);
    #endif


    TargetLocation viewField = NA;
    Actions state = Stop;

    #ifdef PI
        //init sensors
        spiADC mcp3008;
        mcp3008.initSPI(88, 0);
        SharpIR rescue1(mcp3008, 0);
        SharpIR rescue2(mcp3008, 1);
        SharpIR rescue3(mcp3008, 2);
        SharpIR rescue4(mcp3008, 3);
        SharpIR rescue5(mcp3008, 4);
        PixyCam eye;
        eye.init();
    #endif

    //init interface
    Flyintel flyintel;
    SpikesHandler handler;

    #ifdef PI
        //init motors
        DCmotor front(22, 23, 24, 25, 13, 19);
        DCmotor rear(4, 0, 1, 5, 13, 19);
        front.velocity(1000, 1000);
        rear.velocity(1000, 1000);
    #endif

    //open conf pro files
    auto t = getDateTime();
    string conf_file = "./networks/network35.conf", pro_file = "./networks/network35.pro", spike_log = "events-" + t + ".log";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
    cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;
    ofstream fp(spike_log);


//==============================================================================
    //main loop
    for(int round=0; round<200; ++round)
    {
        digitalWrite(16, HIGH);
        fp<<"Round:"<<round<<'\n';
        chrono::steady_clock::time_point timer1;
        timerStart(timer1);

        //baseline activity
        SendFreq("FS1", 2000);
        SendFreq("FS2", 2000);
        SendFreq("FS3", 2000);
        SendFreq("FS4", 2000);

//==============================================================================
        float area = 0;
        if(CUTOFF_PIXY)
        {
            area = 0;
            float dx = 0;
            viewField = CC;
        }
        else
        {
            #ifdef PI
            //pixy cam
                eye.refresh();
                eye.capture();
                array<Obj, 2> retina;
                retina = eye.pickLarge();
                float dx = retina[0].second - PIXY2_CENTER_X;
                area = retina[0].first;

                if(area >= 2200)
                {
                    area = 2200;
                }
                else
                {
                    area = 0;
                }

            #else
                //artificial target
                //float area = 3000;
                float dx = 0;
                viewField = CC;
            #endif
        }
        fp<<"area="<<area<<", dx"<<dx<<endl;
        if(area)
        {
            if(dx > 90)
            {
                SendFreq("FS1", 2000);
                SendFreq("FS3", 2000);
                SendFreq("FS4", area);
                viewField = CR;
            }
            else if(dx < -90)
            {
                SendFreq("FS1", 2000);
                SendFreq("FS3", area);
                SendFreq("FS4", 2000);
                viewField = CL;
            }
            else
            {
                SendFreq("FS1", area);
                SendFreq("FS3", 2000);
                SendFreq("FS4", 2000);
                viewField = CC;
            }
        }

        //IR
        #ifdef PI
            float irFL = rescue1.IRrange();
            float irFC = rescue2.IRrange();
            float irFR = rescue3.IRrange();
            float irBL = rescue4.IRrange();
            float irBR = rescue5.IRrange();
        #endif

            if(irFL > 280)
            {
                SendFreq("TS1", 7000);
            }
            else
            {
                //SendFreq("TS3", 6000-(6000/100.0)*(500-irL));
                SendFreq("TS1", 0);
            }

            if(irFC > 300)
            {
                SendFreq("TS2", 7000);
            }
            else
            {
                SendFreq("TS2", 0);
            }

            if(irFR > 280)
            {
                SendFreq("TS3", 7000);
            }
            else
            {
                //SendFreq("TS4", (6000-(6000/100.0)*(500-irR)));
                SendFreq("TS3", 0);
            }

            if(irBL > 250)
            {
                SendFreq("TS4", 7000);
            }
            else
            {
                //SendFreq("TS1", (6000-(6000/100.0)*(500-irR)));
                SendFreq("TS4", 0);
            }

            if(irBR > 250)
            {
                SendFreq("TS5", 7000);
            }
            else
            {
               // SendFreq("TS2", (6000-(6000/100.0)*(500-irR)));
                SendFreq("TS5", 0);
            }

            fp<<"IR: "<<irFL<<", "<<irFC<<", "<<irFR<<", "<<irBL<<", "<<irBR<<endl;

        #endif

//==============================================================================
        Spikes = ActiveSimGetSpike("530");
        cout<<"receving\n";

        //c-string to int array
        handler.clear();
        handler.cstoi(Spikes);
        handler.printSpikesLog(fp);
//==============================================================================

        //Decode motor neurons
        flyintel.clear();
        flyintel.sortingHat(handler);
        motor motorNeuron = flyintel.getMotor();
        char dir = motorNeuron.first;

        if(dir & 0x01)
        {
            #ifdef PI
                front.forward();
                rear.forward();
                delay(200);
                front.stop();
                rear.stop();
            #endif
            state = Forward;
            cout<<'F'<<endl;
        }
        else if(dir & 0x02)
        {
            #ifdef PI
                front.backward();
                rear.backward();
                delay(200);
                front.stop();
                rear.stop();
            #endif
            state = Backward;
            cout<<'B'<<endl;
        }
        else if(dir & 0x04)
        {
            #ifdef PI
                front.left();
                rear.left();
                delay(200);
                front.stop();
                rear.stop();
            #endif
            state = Left;
            cout<<'L'<<endl;
        }
        else if(dir & 0x08)
        {
            #ifdef PI
                front.right();
                rear.right();
                delay(200);
                front.stop();
                rear.stop();
            #endif
            state = Right;
            cout<<'R'<<endl;
        }
        else
        {
            #ifdef PI
                front.stop();
		delay(200);
                rear.stop();
            #endif
            state = Stop;
            cout<<'S'<<endl;
        }


        fp<<"TIME iteration: "<<timerGetMillis(timer1)<<" ms"<<'\n';

    }
    #ifdef PI
        pwmWrite(19, 0);
        pwmWrite(13, 0);
        digitalWrite(22, LOW);
        digitalWrite(23, LOW);
        digitalWrite(24, LOW);
        digitalWrite(25, LOW);
        digitalWrite(4, LOW);
        digitalWrite(0, LOW);
        digitalWrite(1, LOW);
        digitalWrite(5, LOW);
        digitalWrite(20, LOW);
        digitalWrite(16, LOW);
    #endif
    CloseSim();

    #ifdef DEBUG
        fp.close();
    #endif

    return 0;
}
