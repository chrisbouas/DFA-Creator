#ifndef DFA_H
#define DFA_H
#include "State.h"
#include <cstring>

using namespace std;


class DFA
{
    public:
        DFA();
        bool isDFA(); //Checks if the finite automaton, created, is a DFA
        int findpos(int id); //Returns the position of a state in the array
        bool isTerminal(int id); //Checks whether or not a state is a terminal state

        bool setInitial(int id); //Sets the state, with the id given, an initial state
        bool setTerminal(int id); //Sets the state, with the id given, a terminal state

        void addState(int id); //Adds a new state
        void removeState(int id); //Removes a state
        void setAlphaTransition(int id1, int id2); //An a transition from the state with id1 to the state with id2
        void setBetaTransition(int id1, int id2);//A b transition from the state with id1 to the state with id2

        void showDFA(); //Shows all the states, transitions among the states, and initial/terminal states
        bool testDFA(string s); //Checks if a particular string is accepted by the DFA

    private:
        State **states;
        int numOfStates; //Stores the number of states the DFA has
        int initial; //Stores the id of the initial state
        int *terminal; //Stores the ids of all terminal states
        int numOfTerminalStates; //Stores the number of terminal states
        State *currentState; //Pointer to the current state | Used in transition()
        void transition(char c); //Executes a transition from the current state, to another state, depending one the input
};


#endif // DFA_H
