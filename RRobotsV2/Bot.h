#pragma once
#include "LinkedList.h"
#include "WayType.h"
class Bot{
    public:
    Bot(int difficulty);
    ~Bot();


    private:
    int difficulty;
    LinkedList<WayType> moves;

};

