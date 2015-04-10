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
        this->people = new List<Person>();
        this->states = new List<State>();
        this->states->setEnforceUniqueItems(true);
    }

    ~Database(){

        delete this->people;
        delete this->states;

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
            cout << "Error: Unable to open file" << endl;
        }
    }

    List<Person>* getPeople(){
        return this->people;
    }

    List<State>* getStates(){
        return this->states;
    }

    void listStates(){
        int i = 0;
        ListNode<State> *currentHead = this->getStates()->getHead();
        while(currentHead){
            cout << i+1 << ": " << currentHead->getData()->getState() << endl;
            i++;
            currentHead = currentHead->getNext();
        }
    }

    void listPeopleInState(string stateAbrev){

        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);

        ListNode<State>* stateNode = this->states->find(newStateNode);
        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }

    }

    void findPerson(string firstName, string lastName){



        Person* newPerson = new Person(firstName, lastName);
        ListNode<Person>* newPersonNode = new ListNode<Person>(newPerson);

        ListNode<Person>* personNode = this->people->find(newPersonNode);
        if(personNode){
            cout << "  -- FOUND: " ;
            personNode->getData()->printInfoInline();
        }else{
            cout << " -- " << firstName << " " << lastName << " is not in the list of people" << endl;
        }

    }

    void findPerson(string ssn){

        Person* newPerson = new Person(ssn);
        ListNode<Person>* newPersonNode = new ListNode<Person>(newPerson);

        ListNode<Person>* personNode = this->people->find(newPersonNode);
        if(personNode){
            personNode->getData()->printInfoInline();
        }else{
            cout << " -- the person with the ssn " << ssn << " is not in the list of people" << endl;
        }
    }


    void findOldest(string stateAbrev){
        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);

        ListNode<State>* stateNode = this->states->find(newStateNode);
        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            Person* oldest = currentPerson->getData();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                if(currentPerson->getNext() != NULL){
                    if(*currentPerson->getData()->getBirthday() < *oldest->getBirthday()){
                        oldest = currentPerson->getData();
                    }
                }
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }

            cout << "The oldest person in " << stateAbrev << " is  ";
            oldest->printInfoInline();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }

    }

    void findYoungest(string stateAbrev){
        State* newState = new State(stateAbrev);
        ListNode<State>* newStateNode = new ListNode<State>(newState);

        ListNode<State>* stateNode = this->states->find(newStateNode);
        if(stateNode){
            State *headState = stateNode->getData();
            List<Person>* peopleInState = headState->getPeople();
            cout << "State: " << headState->getState() << endl;
            ListNode<Person>* currentPerson = peopleInState->getHead();
            Person* youngest = currentPerson->getData();
            while(currentPerson){
                //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
                cout << "    - " ;
                if(currentPerson->getNext() != NULL){
                    if(*currentPerson->getData()->getBirthday() > *youngest->getBirthday()){
                        youngest = currentPerson->getData();
                    }
                }
                currentPerson->getData()->printInfoInline();
                currentPerson = currentPerson->getNext();
            }

            cout << "The youngest person in " << stateAbrev << " is  ";
            youngest->printInfoInline();
        }else{
            cout << " -- " << stateAbrev << " is not in the list of states" << endl;
        }
    }


};

#endif //SUEC2A4_DATABASE_HPP
