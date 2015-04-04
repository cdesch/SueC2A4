//
// Created by cj on 4/4/15.
//

#ifndef SUEC2A4_DATABASE_HPP
#define SUEC2A4_DATABASE_HPP

#include "date.hpp"
#include "person.hpp"
#include "state.h"
#include "list.hpp"
#include "listNode.hpp"
#include <fstream>
#include <sstream>



class Database{

protected:
    List<Person>* people;
    List<State>* states;


public:

    int numberOfRecordsCounted = 0;
    Database(){
        this->people =  new List<Person>();
        this->states = new List<State>();
        this->states->setEnforceUniqueItems(true);
    }


    void readfile(string filename){
        this->numberOfRecordsCounted = 1;

        ifstream infile(filename); //Open the file
        string str; // Declares a string and is used for temporary storage
        if (infile.is_open()){
            while (getline(infile,str)){
                string dateString;
                string ssnString;
                string firstName;
                string lastName;
                string stateString;

                string token;
                stringstream stringStream(str);

                //Get Birthday
                if (getline(stringStream, token, ' ')){
                    dateString = token;
                }
                //Get SSN
                if (getline(stringStream, token, ' ')){
                    ssnString = token;
                }
                //Get First Name
                if (getline(stringStream, token, ' ')){
                    firstName = token;
                }
                //Get Last Name
                if (getline(stringStream, token, ' ')){
                    lastName = token;
                }
                //Get State
                if (getline(stringStream, token, ' ')){
                    stateString = token;
                }

                //cout << "Birthdate: " << dateString << " ssn: " << ssnString << " firstname: " << firstName << " lastname: " << lastName << " state: " << stateString << endl;


                Date* birthdate = new Date(dateString); //Creates a new date object

                State* state = new State(stateString); //creating a new state
                state = this->states->addNode(state); //add it to the list BUT if there is already a state of the same name in it, return that state instead

                Person* person = new Person(ssnString, firstName, lastName, birthdate, state);
                state->addPerson(person);
                this->people->addNode(person);

                //person->printInfo();

                this->numberOfRecordsCounted ++;

            }
            infile.close();
        }
        else{
            cout << "Unable to open file" << endl << endl;
        }
    }

    List<Person>* getPeople(){
        return this->people;
    }

    List<State>* getStates(){
        return this->states;
    }

};

#endif //SUEC2A4_DATABASE_HPP
