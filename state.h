//
// Created by cj on 4/2/15.
//

#ifndef SUEC2A4_STATE_HPP
#define SUEC2A4_STATE_HPP

#include <string>
#include <iostream>

using namespace std;

class State{

protected:
    string stateAbbreviation;

public:
    State(){
        this->stateAbbreviation = "";
    }

    State(string abbreviation){
        this->stateAbbreviation = abbreviation;
    }

    ~State(){};

    //Setters & Getters
    void setState(string abbreviation){
        this->stateAbbreviation = abbreviation;
    }

    string getState() const{
        return this->stateAbbreviation;
    }


    bool operator==(const State& object){
        if(this->getState() == object.getState()){
            return true;
        }else{
            return false;
        }
    }

    bool operator!=(const State& object){
        if(this->getState() == object.getState()){
            return false;
        }else{
            return true;
        }
    }



};




#endif //SUEC2A4_STATE_HPP
