#ifndef STATE_H
#define STATE_H
#include <iostream>


class State
{
    public:
        State(int id);
        int value;
        int *transitions;
};


#endif // STATE_H
