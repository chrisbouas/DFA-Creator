#include "DFA.h"
#include <iostream>

DFA::DFA(char* sym, int n)
{
    states = new State*;
    numOfStates = 0;

    numOfSymbols = n;
    DFAsymbols = new char[numOfSymbols];
    DFAsymbols = sym;

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

int DFA::findchar(char s)
{
    for (int i=0;i<numOfSymbols;i++)
    {
        if (DFAsymbols[i] == s)
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
    int temp = findpos(id);
    if (temp == -1)
    {
        cout << "Could not find a state with given id" << endl;
        return 0;
    }

    initial = temp;
    cout << id << " is now the initial state" << endl;
    currentState = states[temp];
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

    delete[] terminal;
    terminal = temp;
    numOfTerminalStates++;
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

    states[numOfStates-1]->transitions = new int[numOfSymbols];
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

void DFA::setTransition(int id1, int id2, char sym)
{
    int pos1 = findpos(id1);
    int pos2 = findpos(id2);
    if (pos1 == -1 || pos2 == -1)
        return;

    int temp = findchar(sym);
    if (temp == -1)
        return;

    states[pos1]->transitions[temp] = id2;
    cout << "Set " << sym << " transition from " << id1 << " to " << id2 << endl;
}

bool DFA::isDFA()
{
    if (initial == -1 || terminal == NULL)
        return 0;

    int i,j;

    for (i=0;i<numOfStates;i++)
    {
        for (j=0;j<numOfSymbols;j++)
        {
            if ((states[i]->transitions[j] < 0) || (states[i]->transitions[j] >= numOfStates))
                return 0;
        }
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

        for (int j=0;j<numOfSymbols;j++)
        {
            cout << states[i]->value << "  -" << DFAsymbols[j] << "->  " << states[i]->transitions[j] << endl;
        }
        cout << endl;
    }
}

int DFA::findnextstate(State* current, char c)
{
    int pos = findpos(current->value);
    int temp = findchar(c);

    int next = states[pos]->transitions[temp]; //Result is an id (int)
    return findpos(next);
}

void DFA::transition(char c)
{
    if (findchar(c) == -1)
        return;

    int pos = findnextstate(currentState,c);
    currentState = states[pos];
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

