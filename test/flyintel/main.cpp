#include "signal.h"
#include <iostream>
#include <fstream>
#include <array>
#include "connect_to_flysim.h"
#include "SCXmodel.h"

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused)
{
   //On CTRL+C - abort! //
    run_flag = false;
    CloseSim();
}

char *Spikes = nullptr;

int main()
{

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

    string conf_file = "../../networks/network30.conf", pro_file = "../../networks/network30.pro";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    signal(SIGINT, handle_SIGINT);

    for(int round=0; round<1000; ++round)
    {
        clock_t tik = clock();

        if(round == 10)
        {
            newTarget = true;
            state = Stop;
        }
        else if(round > 100)
        {
            state = Left;

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
        CXsti.stiLoc(6, 500);
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


        Spikes = ActiveSimGetSpike("250");
        cout
    <<"receving\n";
//      cout<<"Spikes:"<<endl<<Spikes<<endl;

        auto tmp = CXdecode.sortingHat(Spikes);

        for(auto it=tmp.cbegin(); it!=tmp.cend(); ++it)
      {
           fp<<*it<<' ';
        }
        auto ans (CXdecode.findBump());

        fp<<endl;
        cout<<endl;
        CXdecode.clean();

        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }
    return 0;
}
