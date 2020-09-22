#include "StateMachine.h"

void StateMachine::init(Renderer renderer){
    AbstractState* state = this->mStates.at(this->mCurState);
    state->init(renderer);
}
void StateMachine::loop(Renderer renderer){
    AbstractState* state = this->mStates.at(this->mCurState);
    typedef std::chrono::duration<int,std::milli> milliSec;
    //this->tp2 = std::chrono::system_clock::now();
    this->tp2 =  std::chrono::time_point_cast<milliSec>(std::chrono::system_clock::now());

    state->tick(tp2 - tp1);
    this->tp1 = std::chrono::time_point_cast<milliSec>(std::chrono::system_clock::now());
    state->render(renderer);
}
void StateMachine::finish(Renderer renderer){
    
}

void StateMachine::addState(std::string name, AbstractState* newState){
    mStates.insert(std::pair<std::string,AbstractState*>(name,newState));
}

void StateMachine::setStartState(std::string name){
    mCurState = name;
}
