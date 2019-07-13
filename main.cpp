#include <iostream>
#include "DFA.h"

using namespace std;

int main()
{
    DFA re("ab", 2); //regex for language (ab*a)
    string test = "abbbba";

    //create states
    re.addState(0); //init
    re.addState(1);
    re.addState(2); //terminal
    re.addState(3); //black-hole

    //set init & terminal states
    re.setInitial(0);
    re.setTerminal(2);

    //set transitions
    re.setTransition(0,1,'a');
    re.setTransition(0,3,'b');
    re.setTransition(1,2,'a');
    re.setTransition(1,1,'b');
    re.setTransition(2,3,'a');
    re.setTransition(2,3,'b');
    re.setTransition(3,3,'a');
    re.setTransition(3,3,'b');

    cout << "Word \"" << test << "\" is" << (re.testDFA(test)?" ":" not ") << "accepted by DFA." << endl;

    return 0;
}
