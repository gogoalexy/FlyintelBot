#include <iostream>
#include <fstream>
#include <array>
#include "connect_to_flysim.h"
#include "spikesHandler.h"
#include "flyintel.h"
#include "SCXmodel.h"
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

int main()
{
    #ifdef DEBUG
        cout<<"========================================"<<'\n'
            <<"[Initializing Flyintel in DEBUG mode...]"<<'\n'
            <<"========================================"<<endl;
    #else
        cout<<"========================================"<<'\n'
            <<"[        Initializing Flyintel ...     ]"<<'\n'
            <<"========================================"<<endl;
    #endif

    #ifdef PI
        //wiringPi init in BCM pinout
        wiringPiSetupGpio();
        pinMode(16, OUTPUT);
        pinMode(20, OUTPUT);
        digitalWrite(16, LOW);
        digitalWrite(20, LOW);
    #endif

    bool lastBlock = false;
    bool holdTarget = false;
    bool newTarget = false;
    int pastNew = -1;
    int newTargetInterval = 3;

    TargetLocation viewField = NA;
    Actions state = Stop;

    //log file
    #ifdef DEBUG
        fstream fp;
        fp.open("Flyintel.log", ios::out);
    #endif

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
    SimpleCXStimulator CXsti;
    SimpleCXDecoder CXdecode;
    #ifdef PI
        SimpleCXMonitor CXled;
        CXled.init();
    #endif

    #ifdef PI
        //init motors
        DCmotor front(22, 23, 24, 25, 13, 19);
        DCmotor rear(4, 0, 1, 5, 13, 19);
        front.velocity(1000, 1000);//400 for carpet
        rear.velocity(1000, 1000);
    #endif

    //open conf pro files
    string conf_file = "./networks/network35.conf", pro_file = "./networks/network35.pro";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
    cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

//==============================================================================
    //main loop
    for(int round=0; round<250; ++round)
    {
        #ifdef DEBUG
            fp<<"Round:"<<round<<'\n';
            chrono::steady_clock::time_point timer1;
            timerStart(timer1);
        #endif

        //baseline activity
        SendFreq("FS1", 2000);
        SendFreq("FS2", 2000);
        SendFreq("FS3", 2000);
        SendFreq("FS4", 2000);

//------------------------------------------------------------------------------
        #ifdef PI
            //pixy cam
            eye.refresh();
            eye.capture();
            array<Obj, 2> retina;
            retina = eye.pickLarge();
            float dx = retina[0].second - PIXY2_CENTER_X;
            float area = retina[0].first;

            if(area > 5000)
            {
                area = 5000;
            }
            else if(area >= 2500 && area < 4000)
            {
                area = 3000;
            }

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

            #ifdef DEBUG
                cout<<"area="<<area<<", dx"<<dx<<endl;
            #endif
        #else
            //artificial target
            float area = 3000;
            float dx = 0;
            viewField = CC;
        #endif

        if(area && !lastBlock)
        {
            newTarget = true;
            lastBlock = true;
        }
        else if(area && lastBlock)
        {
            newTarget = false;
        }
        else if(!area && lastBlock)
        {
            lastBlock = false;
        }

//==============================================================================

        //scheduler
        if(pastNew >= 0)
        {
            cout<<"******Pastnew"<<pastNew<<'\n';
            //CXsti.rmAllSti();
            CXsti.stiLoc(pastNew, 0);
            pastNew = -1;
            holdTarget = true;
        }
        else if(newTarget)
        {
            cout<<"*****NewTar"<<'\n';
            //CXsti.rmAllSti();
            CXsti.stiLoc(static_cast<int>(viewField), 400);
            newTarget = false;
            holdTarget = false;
            pastNew = static_cast<int>(viewField);
        }
        else if(holdTarget)
        {
            if(state == Stop)
            {
                cout<<"stop"<<'\n';
                CXsti.switchState();
            }
            else if(state == Forward)
            {
                cout<<"straight"<<'\n';
                CXsti.switchState();
            }
            else if(state == Backward)
            {
                cout<<"back"<<'\n';
                CXsti.switchState();
            }
            else if(state == Left)
            {
                cout<<"left"<<'\n';
                CXsti.switchState();
                CXsti.shiftRight(200);
            }
            else if(state == Right)
            {
                cout<<"right"<<'\n';
                CXsti.switchState();
                CXsti.shiftLeft(200);
            }
        }
        else
        {
            cout<<"No sti"<<'\n';
        }

//==============================================================================

        //IR
        #ifdef PI
            float irFL = rescue1.IRrange();
            float irFC = rescue2.IRrange();
            float irFR = rescue3.IRrange();
            float irBL = rescue4.IRrange();
            float irBR = rescue5.IRrange();

            if(irFL > 250)
            {
                SendFreq("TS1", 5000);
            }
            else
            {
                //SendFreq("TS3", 6000-(6000/100.0)*(500-irL));
                SendFreq("TS1", 0);
            }

            if(irFC > 250)
            {
                SendFreq("TS2", 5000);
            }
            else
            {
                SendFreq("TS2", 0);
            }

            if(irFR > 250)
            {
                SendFreq("TS3", 5000);
            }
            else
            {
                //SendFreq("TS4", (6000-(6000/100.0)*(500-irR)));
                SendFreq("TS3", 0);
            }

            if(irBL > 250)
            {
                SendFreq("TS4", 5000);
            }
            else
            {
                //SendFreq("TS1", (6000-(6000/100.0)*(500-irR)));
                SendFreq("TS4", 0);
            }

            if(irBR > 250)
            {
                SendFreq("TS5", 5000);
            }
            else
            {
               // SendFreq("TS2", (6000-(6000/100.0)*(500-irR)));
                SendFreq("TS5", 0);
            }

            cout<<"IR: "<<irFL<<", "<<irFC<<", "<<irFR<<", "<<irBL<<", "<<irBR<<endl;

        #else
            //artificial inputs
        #endif

//==============================================================================
        #ifdef DEBUG
            chrono::steady_clock::time_point timer2;
            timerStart(timer2);
        #endif

        Spikes = ActiveSimGetSpike("530");
        cout<<"receving\n";
        cout<<Spikes<<endl;
        #ifdef DEBUG
            fp<<"TIME simulation: "<<timerGetMillis(timer2)<<" ms"<<'\n';
        #endif

        //c-string to int array
        handler.clear();
        handler.cstoi(Spikes);
        #ifdef DEBUG
            handler.printSpikesLog(fp);
        #endif
//==============================================================================

        //Decode CX
        auto tmp = CXdecode.sortingHat(handler);

        #ifdef DEBUG
            for(auto it=tmp.cbegin(); it!=tmp.cend(); ++it)
            {
                fp<<*it<<' ';
            }
        #endif

        auto ans (CXdecode.findBump());
        #ifdef PI
            CXled.flush();
            CXled.showBump(ans);
        #endif

        #ifdef DEBUG
            fp<<endl;
            cout<<endl;
        #endif

        #ifdef PI
            //homing stage
            if(round == 281)
            {
                //homing starts
                delay(2000);
                digitalWrite(20, HIGH);
            }
            if(round > 280)
            {
                if( ans.front() == 0)
                    return 0;
                digitalWrite(20, HIGH);
                while(!ans.empty())
                {
                    if(ans.front() == 0 || ans.front() == 1 || ans.front() == 15)
                    {
                        SendFreq("FS1", 4000);
                        break;
                    }
                    else if(ans.front() < 8)
                    {
                        SendFreq("FS4", 4000);
                        ans.pop();
                    }
                    else if(ans.front() >= 8)
                    {
                        SendFreq("FS3", 4000);
                        ans.pop();
                    }
                }
            }
        #endif
//------------------------------------------------------------------------------

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

        #ifdef DEBUG
            fp<<"TIME iteration: "<<timerGetMillis(timer1)<<" ms"<<'\n';
        #endif
    }
    #ifdef PI
        CXled.flush();
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
    #endif
    CloseSim();

    #ifdef DEBUG
        fp.close();
    #endif

    return 0;
}
