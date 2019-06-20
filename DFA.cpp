#include "DFA.h"
#include <iostream>

DFA::DFA()
{
    states = new State*;
    numOfStates = 0;
    initial = -1;
    terminal = NULL;
    numOfTerminalStates = 0;
    currentState = NULL;
}

int DFA::findpos(int id)
{
    for (int i=0;i<numOfStates;i++)
    {
        if (states[i]->value == id)
            return i;
    }
    return -1;
}

bool DFA::isTerminal(int id)
{
    for (int i=0;i<numOfTerminalStates;i++)
    {
        if (terminal[i] == id)
            return 1;
    }
    return 0;
}

bool DFA::setInitial(int id)
{
    if (findpos(id) == -1)
    {
        cout << "Could not find a state with given id" << endl;
        return 0;
    }

    initial = findpos(id);
    cout << id << " is now the initial state" << endl;
    currentState = states[findpos(id)];
    return 1;
}

bool DFA::setTerminal(int id)
{
    if (findpos(id) == -1)
    {
        cout << "Could not find a state with given id" << endl;
        return 0;
    }
    else if (isTerminal(id))
    {
        cout << "State is already a terminal state" << endl;
        return 0;
    }

    int i;
    int *temp;
    temp = new int[numOfTerminalStates+1];
    for (i=0;i<numOfTerminalStates;i++)
    {
        temp[i] = terminal[i];
    }
    temp[i] = id;

    numOfTerminalStates++;
    terminal = new int[numOfTerminalStates];
    terminal = temp;
    cout << id << " is now a final state" << endl;
    return 1;
}

void DFA::addState(int id)
{
    int i;

    if (findpos(id) != -1)
        return;

    State **temp;
    temp = new State*[numOfStates+1];
    for (i=0;i<numOfStates;i++)
    {
        temp[i] = states[i];
    }
    temp[i] = new State(id);
    delete[] states;

    numOfStates++;
    states = new State*[numOfStates];
    states = temp;
    cout << "Added state " << id << endl;
}

void DFA::removeState(int id)
{
    int i, j;

    if (findpos(id) == -1)
        return;

    State **temp;
    temp = new State*[numOfStates-1];
    j=0;
    for (i=0;i<numOfStates;i++)
    {
        if (i != findpos(id))
        {
            temp[j] = states[i];
            j++;
        }
    }
    delete[] states;

    numOfStates--;
    states = new State*[numOfStates];
    states = temp;
    cout << "Removed state " << id << endl;
}

void DFA::setAlphaTransition(int id1, int id2)
{
    if (findpos(id1) == -1 || findpos(id2) == -1)
        return;

    states[findpos(id1)]->alpha = states[findpos(id2)];
    cout << "Set alpha transition from " << id1 << " to " << id2 << endl;
}
void DFA::setBetaTransition(int id1, int id2)
{
    if (findpos(id1) == -1 || findpos(id2) == -1)
        return;

    states[findpos(id1)]->beta = states[findpos(id2)];
    cout << "Set beta transition from " << id1 << " to " << id2 << endl;
}

bool DFA::isDFA()
{
    if (initial == -1 || terminal == NULL)
        return 0;

    for (int i=0;i<numOfStates;i++)
    {
        if (states[i]->alpha == NULL || states[i]->beta == NULL)
            return 0;
    }
    return 1;
}

void DFA::showDFA()
{
    if (!isDFA())
    {
        cout << "The finite automaton is not deterministic" << endl;
        return;
    }

    for (int i=0;i<numOfStates;i++)
    {
        cout << "State " << states[i]->value << endl;
        if (states[i]->value == initial)
            cout << states[i]->value << " is the initial state" << endl;
        else if (isTerminal(states[i]->value))
            cout << states[i]->value << " is a terminal state" << endl;

        cout << states[i]->value << "  -a->  " << states[i]->alpha->value << endl;
        cout << states[i]->value << "  -b->  " << states[i]->beta->value << endl;
        cout << endl;
    }
}

void DFA::transition(char c)
{
    if (c == 'a')
        currentState = currentState->alpha;
    else if (c == 'b')
        currentState = currentState->beta;
}

bool DFA::testDFA(string s)
{
    if (s == "" && isTerminal(currentState->value))
        return 1;
    else if (s == "" && !isTerminal(currentState->value))
        return 0;

    transition(s[0]);
    s.erase(s.begin());
    return testDFA(s);
}
