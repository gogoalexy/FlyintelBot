#include <fstream>
#include <array>
#include <utulity>
#include "DCmotor.h"
#include "connect_to_flysim.h"
#include "SCXmodel.h"

using namespace std;

char *Spikes = nullptr;

fstream fp;
fp.open("rotation.log", ios::out);

//
//command: 
//

int main()
{
    DCmotor front();
    DCmotor rear();
    
    SimpleCXStimulator sti;
    SimpleCXDecoder deco;
    SimpleCXMonitor moni;

    //speed, duration
    array<pair<char, int>, 12> actions
    {
        actions[0] = make_pair('F', 600);
        actions[1] = make_pair('S', 600);
        actions[2] = make_pair('R', 600);
        actions[3] = make_pair('S', 600);
        actions[4] = make_pair('L', 600);
        actions[5] = make_pair('S', 600);
        actions[6] = make_pair('B', 600);
        actions[7] = make_pair('S', 600);
        actions[8] = make_pair('R', 600);
        actions[9] = make_pair('S', 600);
        actions[10] = make_pair('L', 600);
        actions[11] = make_pair('S', 600);
    };
    
    for(auto it = actions.cbegin(); it != actions.cend(); ++i)
    {
        char direction = it->first;
        int duration = it->second;

        front.velocity(speed, speed);
        rear.velocity(speed, speed);

        switch(direction)
        {
            case 'S' :
                front.stop();
                rear.stop();
                break;
            case 'F' :
                front.forward();
                rear.forward();
                break;
            case 'B' :
                front.backward();
                rear.backward();
                break;
            case 'L' :
                front.left();
                rear.left();
                sti.shiftLeft();
                break;
            case 'R' :
                front.right();
                rear.right();
                sti.shiftRight();
                break;       
        }

        Spikes = ActiveSimGetSpike("250");
        CXled.flush();
        auto tmp = CXdecode.sortingHat(Spikes);
        for(auto ait = tmp.cbegin(); ait != tmp.cend(); ++ait)
        {
            fp<<*ait<<' ';
        }
        auto pos (CXdecode.findBump());
        CXled.showBump(pos);
        fp<<endl;
        cout<<endl;
        CXdecode.clean();
        delay(duration);
        
    }
    return 0;
}

    
