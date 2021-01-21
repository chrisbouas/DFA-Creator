#include "State.h"

State::State(int id)
{
    value = id;
    transitions = std::make_unique<std::unordered_map<int,int>>();
}

inline bool operator==(const State& lhs, const State& rhs){
    return lhs.value == rhs.value;
}

inline bool operator!=(const State& lhs, const State& rhs){
    return !(lhs == rhs);
}