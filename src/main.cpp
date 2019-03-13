#include "signal.h"
#include <iostream>
#include <fstream>
#include <array>
#include <wiringPi.h>
#include "connect_to_flysim.h"
#include "SCXmodel.h"
#include "pixycam.h"
#include "DCmotor.h"

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
    wiringPiSetupGpio();
    bool lastBlock = false;
    bool holdTarget = false;
    bool newTarget = false;
    int pastNew = -1;
    enum Actions{Stop, Forward, Backward, Left, Right};
    Actions state = Stop;

    fstream fp;
    fp.open("Flyintel.log", ios::out);

    SimpleCXStimulator CXsti;
    SimpleCXDecoder CXdecode;
    SimpleCXMonitor CXled;
    CXled.init();

//    PixyCam eye;
  //  eye.init();
    DCmotor front(22, 23, 24, 25, 13, 19);
    DCmotor rear(4, 0, 1, 5, 13, 19);
    front.velocity(300, 300);//400 for carpet
    rear.velocity(300, 300);

    string conf_file = "./networks/network30.conf", pro_file = "./networks/network30.pro";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    signal(SIGINT, handle_SIGINT);

    for(int round=0; round<1000; ++round)
    {
        clock_t tik = clock();

    //    eye.refresh();
  //      eye.capture();
//        eye.pickLarge();
      //  array<Obj, 2> retina;
        //retina = eye.pickLarge();
        /*if(retina.first && !lastBlock)
        {
            newTarget = true;
            lastBlock = true;
        }
        else if(retina.first && lastBlock)
        {
            newTarget = false;
        }
        else if(!retina.first && lastBlock)
        {
            lastBlock = false;
        }*/
        if(round == 5)
        {
            newTarget = true;
            state = Stop;
        }
        else if(round > 100)
        {
            state = Left;
           front.right();
            rear.right();
             delay(200);
	front.stop();
	rear.stop();
        }

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
            }
            else if(state == Forward)
            {
                cout<<"straight"<<'\n';
            }
            else if(state == Backward)
            {
                cout<<"back"<<'\n';
            }
            else if(state == Left)
            {
                cout<<"left"<<'\n';
                CXsti.shiftLeft(200);
            }
            else if(state == Right)
            {
                cout<<"right"<<'\n';
                CXsti.shiftRight(200);
            }
        }
        else
        {
            cout<<"No sti"<<'\n';
        }
/*
        float irL = rescue1.IRrange();
        if(irL > 400)
        {
            SendFreq("TS2", 9000);
        }
        else
        {
            SendFreq(9000-(9000/90.0)*(400-irL), 6);//negative issue
        }

        float irR = rescue2.IRrange();
        if(irR > 400)
        {
            SendFreq("TS3", 9000);
        }
        else
        {
            SendFreq("TS3", (int)(9000-(9000/90.0)*(400-irR)));
        }

        cout<<"IR: "<<irL<<", "<<irR<<endl;
*/

        Spikes = ActiveSimGetSpike("600");
        cout
    <<"receving\n";
//      cout<<"Spikes:"<<endl<<Spikes<<endl;
        CXled.flush();
        auto tmp = CXdecode.sortingHat(Spikes);
/*        motor motorNeuron = flyintel.getMotor(flyintel.cstoi(Spikes));
        char dir = motorNeuron.first;
        if(dir == 'S')
            state = Stop;
        else if(dir == 'F')
            state = Forward;
        else if(dir == 'B')
            state = Backward;
        else if(dir == 'L')
            state = Left;
        else if(dir == 'R')
            state = Right;

        int speed = motorNeuron.second;*/
        for(auto it=tmp.cbegin(); it!=tmp.cend(); ++it)
      {
           fp<<*it<<' ';
        }
        auto ans (CXdecode.findBump());
        CXled.showBump(ans);
        fp<<endl;
        cout<<endl;
        CXdecode.clean();

        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }
    return 0;
}
