#ifndef DFA_H
#define DFA_H
#include "State.h"
#include <cstring>
#include <vector>
#include <memory>

// Alias UniqueVec to a unique_ptr to a vector of custom type T
template<class T>
using UniqueVec = std::unique_ptr<std::vector<T>>;

class DFA
{
    public:
        DFA(std::string, int);
        bool isDFA(); //Checks if the finite automaton, created, is a DFA
        int findpos(int id); //Returns the position of a state in the array
        int findchar(char s); //Returns the position of a character in DFAsymbols

        //INITIAL & TERMINAL STATES
        bool isTerminal(int id); //Checks whether or not a state is a terminal state
        bool setInitial(int id); //Sets the state, with the id given, an initial state
        bool setTerminal(int id); //Sets the state, with the id given, a terminal state

        //STATES & TRANSITIONS
        void addState(int id); //Adds a new state
        void removeState(int id); //Removes a state
        void setTransition(int id1, int id2, char sym); //A sym transition from the state with id1 to the state with id2

        //DISPLAY & TEST DFA
        void showDFA(); //Shows all the states, transitions among the states, and initial/terminal states
        bool testDFA(std::string s); //Checks if a particular string is accepted by the DFA

    private:
        // DFA object owns the states
        UniqueVec<std::unique_ptr<State>> states;
        int numOfStates; //Stores the number of states the DFA has
        UniqueVec<char> DFAsymbols; //Array that stores the alphabet of the regular language
        int numOfSymbols; //Stores the number of symbols the alphabet of the regular language has
        int initial; //Stores the id of the initial state
        UniqueVec<int> terminal; //Stores the ids of all terminal states
        int numOfTerminalStates; //Stores the number of terminal states

        State* currentState; //Pointer to the current state | currentState is a State owned by this object | Used in transition()
        int findnextstate(State* current, char c); //Decides which state should be visited next | Used in transition()
        void transition(char c); //Executes a transition from the current state, to another state, depending one the input
};


#endif // DFA_H
