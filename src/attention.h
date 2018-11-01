#ifndef ATTENTION_H

#include <cstdio> //sprintf is used in pixy.h but not included lol
#include <iostream>
#include <utility>
#include <queue>
#include <array>
#include "pixy.h"

#define BLOCK_BUFFER_SIZE 25

typedef pair<int, int> obj;
/*
struct Object {
    float key_area;
    float horizontal;
}
*/
class Attention {
public:
    Attention();
    Attention(int, int);
    int vision_init();
    void refresh();
    void capture();
    std::array<obj, 2> pick();
    ~Attention();
private:
    int FOOD;
    int TOXIC;
    struct Block blocks[BLOCK_BUFFER_SIZE];
    std::priority_queue< obj, vector<obj>, greater<obj> > foodQ;
    std::priority_queue< obj, vector<obj>, greater<obj> > toxicQ;
    std::priority_queue< obj, vector<obj>, greater<obj> > clearQ;
};

#define ATTENTION_H
#endif
