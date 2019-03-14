
#include "signal.h"
#include <iostream>
#include <fstream>
#include <array>
#include <wiringPi.h>
#include "connect_to_flysim.h"
#include "flyintel.h"
#include "SCXmodel.h"
#include "SPIadc.h"
#include "Sharp_IR.h"
#include "HC_SR04.h"
#include "pixycam.h"
#include "DCmotor.h"
//#include "timer.h"

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused)
{
   //On CTRL+C - abort! //
    run_flag = false;
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    digitalWrite(24, LOW);
    digitalWrite(25, LOW);
    digitalWrite(4, LOW);
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(5, LOW);
    CloseSim();
}

char *Spikes = nullptr;

int main()
{
    //wiringPi init in BCM pinout
    wiringPiSetupGpio();

    bool lastBlock = false;
    bool holdTarget = false;
    bool newTarget = false;
    int pastNew = -1;
    int newTargetInterval = 3;
    enum Actions{Stop, Forward, Backward, Left, Right};
    Actions state = Stop;

//    Timer timer;

    //log file
    fstream fp;
    fp.open("Flyintel.log", ios::out);

    //init sensors
    HCSR04 rescue0(21, 26, 10000);
    ADC mcp3008;
        mcp3008.initSPI(88, 0);
    SharpIR rescue1(mcp3008, 0);
    SharpIR rescue2(mcp3008, 1);
    PixyCam eye;
    eye.init();

    //init interface
    Flyintel flyintel;
    SimpleCXStimulator CXsti;
    SimpleCXDecoder CXdecode;
    SimpleCXMonitor CXled;
    CXled.init();

    //init motors
    DCmotor front(22, 23, 24, 25, 13, 19);
    DCmotor rear(4, 0, 1, 5, 13, 19);
    front.velocity(1000, 1000);//400 for carpet
    rear.velocity(1000, 1000);

    //open conf pro files
    string conf_file = "./networks/network31.conf", pro_file = "./networks/network31.pro";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
    cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    signal(SIGINT, handle_SIGINT);

    //main loop
    for(int round=0; round<800; ++round)
    {

  //      timer.start();

        SendFreq("random1", 1500);
        SendFreq("random2", 1500);
        SendFreq("random3", 1700);
        SendFreq("random4", 1700);
        //pixy cam
        eye.refresh();
        eye.capture();
        array<Obj, 2> retina;
        retina = eye.pickLarge();

        float dx = retina[0].second - PIXY2_CENTER_X;
        float area = retina[0].first;
        if(area > 5500)
        {
            area = 5000;
        }
        else if(area >= 2500 && area < 4000)
        {
             area = 4000;
        }

        if(dx > 100)
        {
            SendFreq("FS1", 0);
            SendFreq("FS3", 0);
            SendFreq("FS4", area);
        }
        else if(dx < -100)
        {
            SendFreq("FS1", 0);
            SendFreq("FS3", area);
            SendFreq("FS4", 0);
        }
        else
        {
            SendFreq("FS1", area);
            SendFreq("FS3", 0);
            SendFreq("FS4", 0);
        }
        cout<<"area="<<area<<", dx"<<dx<<endl;

        if(retina[0].first && !lastBlock)
        {
            newTarget = true;
            lastBlock = true;
        }
        else if(retina[0].first && lastBlock)
        {
            newTarget = false;
        }
        else if(!retina[0].first && lastBlock)
        {
            lastBlock = false;
        }

//==============================================================================
/*
        if(round == 5)
        {
            newTarget = true;
            state = Stop;
        }
        else if(round > 100 && round < 150)
        {
            state = Left;
            front.right();
            rear.right();
            delay(200);
            front.stop();
            rear.stop();
        }else if(round > 150 && round < 200)
	{
		state = Right;
		front.left();
		rear.left();
		delay(200);
		front.stop();
		rear.stop();
	}else
	{
		state = Left;
		front.right();
		rear.right();
		delay(200);
		front.stop();
		rear.stop();
	}
*/
        if(pastNew >= 0)
        {
            cout<<"pastnew"<<pastNew<<'\n';
            CXsti.stiLoc(pastNew, 0);
            pastNew = -1;
            holdTarget = true;
        }
        else if(newTarget)
        {
            //.......locate
            cout<<"newTar"<<'\n';
        CXsti.stiLoc(6, 250);
            newTarget = false;
            holdTarget = false;
            pastNew = 6;
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

        //ultra
        unsigned int soundtime = rescue0.UsoundRange();
        if(soundtime < 2000)
        {
            SendFreq("TS1", 9800);
        }
        else
        {
            SendFreq("TS1", (9800-(9800/500.0)*(soundtime-2000)) );
        }
        cout<<"Ultra: "<<soundtime<<"; ";

        //IR
        float irL = rescue1.IRrange();
        if(irL > 400)
        {
            SendFreq("TS2", 9000);
        }
        else
        {
            SendFreq("TS2", 9000-(9000/90.0)*(400-irL));
        }

        float irR = rescue2.IRrange();
        if(irR > 400)
        {
            SendFreq("TS3", 9000);
        }
        else
        {
            SendFreq("TS3", (9000-(9000/90.0)*(400-irR)));
        }
        cout<<"IR: "<<irL<<", "<<irR<<endl;

//==============================================================================

        Spikes = ActiveSimGetSpike("500");
        cout
        <<"receving\n";
        //cout<<"Spikes:"<<endl<<Spikes<<endl;

//==============================================================================

        //Decode motor neurons
        flyintel.refresh();
        motor motorNeuron = flyintel.getMotor(flyintel.cstoi(Spikes));
        char dir = motorNeuron.first;
        int speed = motorNeuron.second;

        if(dir & 0x01)
        {
            cout<<'F'<<endl;
            front.forward();
            rear.forward();
            delay(200);
            front.stop();
            rear.stop();
            state = Forward;
        }
        else if(dir & 0x02)
        {
            cout<<'B'<<endl;
            front.backward();
            rear.backward();
            delay(200);
            front.stop();
            rear.stop();
            state = Backward;
        }
        else if(dir & 0x04)
        {
            cout<<'L'<<endl;
            front.left();
            rear.left();
            delay(200);
            front.stop();
            rear.stop();
            state = Left;
        }
        else if(dir & 0x08)
        {
            cout<<'R'<<endl;
            front.right();
            rear.right();
            delay(200);
            front.stop();
            rear.stop();
            state = Right;
        }
        else
        {
            cout<<'S'<<endl;
            front.stop();
            rear.stop();
            state = Stop;
        }

        //Decode CX
        CXled.flush();
        auto tmp = CXdecode.sortingHat(Spikes);
        for(auto it=tmp.cbegin(); it!=tmp.cend(); ++it)
        {
           fp<<*it<<' ';
        }
        auto ans (CXdecode.findBump());
        CXled.showBump(ans);
        fp<<endl;
        cout<<endl;
        CXdecode.clean();
//        cout<<"loop time: "<<timer.getMillis()<<endl;
    }

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
    CloseSim();
    return 0;
}
