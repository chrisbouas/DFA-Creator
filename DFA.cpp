#include "DFA.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::cout;
using std::endl;

DFA::DFA(std::string sym, int n)
        : numOfSymbols(n), numOfStates(0), initial(-1), numOfTerminalStates(0)
{
    states = std::make_unique<std::vector<std::unique_ptr<State>>>();
    DFAsymbols = std::make_unique<std::vector<char>>(sym.begin(),sym.end());
    terminal = std::make_unique<std::vector<int>>();
    currentState = nullptr;
}

int DFA::findpos(int id)
{
    // Run find with custom comparator
    auto result = std::find_if(states->cbegin(), states->cend(), [&id](auto& s){return s->value == id;});
    // If find result is end search was unsuccessful
    if( result == states->cend()){
        return -1;
    }else{
        return std::distance(states->cbegin(), result);
    }
}

int DFA::findchar(char s)
{
    auto result = std::find(DFAsymbols->cbegin(), DFAsymbols->cend(), s);
    // If find result is end iterator search was unsuccessful
    if( result == DFAsymbols->cend()){
        return -1;
    }else{
        return std::distance(DFAsymbols->cbegin(), result);
    }
}

bool DFA::isTerminal(int id)
{
    // Return if id was found in terminal vector
    return std::find(terminal->cbegin(), terminal->cend(), id) != terminal->cend();
}

bool DFA::setInitial(int id)
{
    int temp = findpos(id);
    if (temp == -1)
    {
        cout << "Could not find a state with given id" << endl;
        return false;
    }

    initial = temp;
    cout << id << " is now the initial state" << endl;
    currentState = states->at(id).get();
    return true;
}

bool DFA::setTerminal(int id)
{
    if (findpos(id) == -1)
    {
        cout << "Could not find a state with given id" << endl;
        return false;
    }
    else if (isTerminal(id))
    {
        cout << "State is already a terminal state" << endl;
        return false;
    }

    terminal->emplace_back(id);

    numOfTerminalStates++;
    cout << id << " is now a final state" << endl;
    return true;
}

void DFA::addState(int id)
{

    if (findpos(id) != -1)
    {
        std::cout << "State with id " << id << "already exists!\n";
        return;
    }

    states->emplace_back(std::make_unique<State>(id));
    numOfStates++;

    cout << "Added state " << id << endl;
}

void DFA::removeState(int id)
{
    unsigned elPos = findpos(id);

    if (elPos == -1)
    {
        return;
    }

    // Delete element at found position
    states->erase(states->begin() + elPos);
    cout << "Removed state " << id << endl;
}

void DFA::setTransition(int id1, int id2, char sym)
{
    int pos1 = findpos(id1);
    int pos2 = findpos(id2);
    if (pos1 == -1 || pos2 == -1)
    {
        return;
    }

    int charPos = findchar(sym);
    if (charPos == -1)
    {
        return;
    }

    // Get origin state
    auto& origin = *(states->at(pos1));
    origin.transitions->emplace(charPos, pos2);
    cout << "Set " << sym << " transition from " << id1 << " to " << id2 << endl;
}

bool DFA::isDFA()
{
    if (initial == -1 || terminal->empty())
        return false;

    for (int i=0;i<numOfStates;i++)
    {
        for (int j=0;j<numOfSymbols;j++)
        {
            auto& origin = states->at(i);
            // If a transition from  state origin with symbol j does not exist
            if (origin->transitions->find(j) == origin->transitions->end())
            {
                return false;
            }
            // Check if transition points to a valid state index. Element transitions j exists 
            // since it was checked before.
            if(origin->transitions->at(j) >= numOfStates)
            {
                return false;
            }
            
        }
    }
    return true;
}

void DFA::showDFA()
{
    if (!isDFA())
    {
        cout << "The finite automaton is not deterministic" << endl;
        return;
    }

    for (auto& state: *states)
    {
        // Print state and id
        cout << "State " << state->value << endl;
        if (state->value == initial)
            cout << state->value << " is the initial state" << endl;
        else if (isTerminal(state->value))
            cout << state->value << " is a terminal state" << endl;


        for (int j=0;j<numOfSymbols;j++)
        {
            std::cout << state->value << "  -" << DFAsymbols->at(j) << "->  " << state->transitions->at(j) << "\n";
        }
        cout << endl;
    }
}

int DFA::findnextstate(State* current, char c)
{
    int pos = findpos(current->value);
    int temp = findchar(c);

    int next  = states->at(pos)->transitions->at(temp); //Result is an id (int)1
    return findpos(next);
}

void DFA::transition(char c)
{
    // See if character is in the DFT alphabet
    if (findchar(c) == -1){
        std::string error{"Invalid character "};
        error.push_back(c);
        throw std::invalid_argument(error);
    }
    int pos = findnextstate(currentState,c);
    currentState = states->at(pos).get();
}

bool DFA::testDFA(std::string s)
{
    if (s.empty() && isTerminal(currentState->value))
        return true;
    else if (s.empty() && !isTerminal(currentState->value))
        return false;

    // Move to next stage depending on next character
    try{
        transition(s[0]);
    } catch (std::invalid_argument& e) {
        std::cout << e.what() << "\n";
        return false;
    }
    s.erase(s.begin());
    return testDFA(s);
}

