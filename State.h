#ifndef STATE_H
#define STATE_H
#include <iostream>
#include <memory>
#include <unordered_map>

class State
{
    public:
        explicit State(int id);
        int value;
        std::unique_ptr<std::unordered_map<int,int>> transitions; // Maps symbol index to state id
};

inline bool operator==(const State&, const State&);
inline bool operator!=(const State&, const State&);

#endif // STATE_H
