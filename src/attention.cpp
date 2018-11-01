#include "attention.h"

Attention::Attention () {
    this->FOOD = 1;
    this->TOXIC = 2;
}

Attention::Attention (int food_sig, int toxic_sig) {
    this->FOOD = food_sig;
    this->TOXIC = toxic_sig;
}

int Attention::vision_init() {
    int pixy_init_status = pixy_init();

  // Was there an error initializing pixy? //
    if(!pixy_init_status == 0) {
    // Error initializing Pixy //
        cout<<"pixy_init(): ";
        pixy_error(pixy_init_status);

        return pixy_init_status;
    }
}

void Attention::refresh() {
    if(!foodQ.empty()) {
        foodQ = clearQ;
    }
    if(!toxicQ.empty()) {
        toxicQ = clearQ;
    }
}

void Attention::capture() {
// Wait for new blocks to be available //
    while(!pixy_blocks_are_new()) {} 

    // Get blocks from Pixy //
    int blocks_copied = pixy_get_blocks(BLOCK_BUFFER_SIZE, &blocks[0]);

    if(blocks_copied < 0) {
      // Error: pixy_get_blocks //
        cout<<"pixy_get_blocks(): ";
        pixy_error(blocks_copied);
    }

    for(int i=0; i!= blocks_copied; ++i) {
        if(blocks[i].signature == FOOD){
            auto food = make_pair(blocks[i].width*blocks[i].height, blocks[i].x);
            foodQ.push(food);
        }else if(blocks[i].signature == TOXIC){
            auto toxic = make_pair(blocks[i].width*blocks[i].height, blocks[i].x);
            toxicQ.push(toxic);
        }else{
            continue;
        }
    }
    
}

array<obj, 2> Attention::pick() {
    array<obj, 2> see;
    
    if(!foodQ.empty()) {
        see[0] = foodQ.top();
    }else{
        see[0] = make_pair(0, 0);
    }
    
    if(!toxicQ.empty()) {
        see[1] = toxicQ.top();
    }else{
        see[1] = make_pair(0, 0);
    }
    
    return see;
}

Attention::~Attention(){
    pixy_close();
    while(!foodQ.empty()){
        foodQ.pop();
    }
    while(!toxicQ.empty()){
        toxicQ.pop();
    }
}
