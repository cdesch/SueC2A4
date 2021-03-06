#include <iostream>
#include "date.hpp"
#include "person.hpp"
#include "state.h"
#include "list.hpp"
#include "listNode.hpp"
#include <cassert>
#include "database.hpp"
#include <fstream>
#include <sstream>
#include <vector>

/*Order
 * Date
 * State
 * Person
 * listNode
 * treeNode
 * list
 * tree
 * database
 * testcases
 * interpreter
 * main
 */


using namespace std;

enum COMMAND { EXIT_PROGRAM, READ, STATES, LIST, OLDEST, YOUNGEST, FIND, MOVE, MERGE, ERROR};

void testDateClass(){
    Date* date = new Date(2015,4,2);
    assert(date->getYear() == 2015);
    assert(date->getMonth() == 4);
    assert(date->getDay() == 2);
}

void testPersonClass(){
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date, state);

    assert(person->getSsn() == "00000000" );
    assert(person->getFirstName() == "MyFirstName" );
    assert(person->getLastName() == "MyLastName" );

    Person* person1 = new Person("00000001", "MyFirstName", "MyLastName", date, state);
    Person* person2 = new Person("00000002", "MyFirstName", "MyLastName", date, state);
    Person* person3 = new Person("00000003", "MyFirstName", "MyLastName", date, state);
    Person* person4 = new Person("00000004", "MyFirstName", "MyLastName", date, state);

    assert(*person1 < *person2);
    assert(*person2 > *person1);
    assert(!(*person2 < *person1));
    assert(*person4 > *person2);
    assert(!(*person1 > *person4));

}

void testStateClass(){

    State* newyork = new State("NY");
    State* newyork1 = new State("NY");
    State* newjersey = new State("NJ");

    assert( *newyork == *newyork1);
    assert( *newyork != *newjersey);

    string NY = "NY";
    string NJ = "NJ";
    assert(NY > NJ);
    assert( *newyork > *newjersey);
    assert( *newjersey < *newyork);
    assert(!(*newjersey > *newyork));
    assert(!(*newyork < *newjersey));
}


void testLinkedListSort(){
    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    State* state1 = new State("NJ");
    State* state2 = new State("AL");
    State* state3 = new State("HI");
    State* state4 = new State("DC");

    Person* person = new Person("00100000", "MyFirstName", "MyLastName", date, state);
    Person* person1 = new Person("00030001", "MyFirstName", "MyLastName", date, state);
    Person* person2 = new Person("010000002", "MyFirstName", "MyLastName", date, state);
    Person* person3 = new Person("00000103", "MyFirstName", "MyLastName", date, state);
    Person* person4 = new Person("00100004", "MyFirstName", "MyLastName", date, state);

    List<Person> *personList = new List<Person>();
    personList->addNode(person);
    personList->addNode(person1);
    personList->addNode(person2);
    personList->addNode(person3);
    personList->addNode(person4);

    personList->sort();


    ListNode<Person>* currentHead = personList->getHead();

    while(currentHead){
        //cout << " " << currentHead->getData()->getSsn() << endl;
        if(currentHead->getNext()){
            assert(*currentHead->getData() < *currentHead->getNext()->getData());
        }
        currentHead = currentHead->getNext();
    }


    List<State> *stateList = new List<State>();
    stateList->addNode(state);
    stateList->addNode(state1);
    stateList->addNode(state2);
    stateList->addNode(state3);
    stateList->addNode(state4);


    stateList->sort();
    ListNode<State>* currentHeadState = stateList->getHead();
    while(currentHeadState){
        //cout << " " << currentHeadState->getData()->getState() << endl;
        if(currentHeadState->getNext()){
            assert(*currentHeadState->getData() < *currentHeadState->getNext()->getData());
        }
        currentHeadState = currentHeadState->getNext();
    }



}

void testLinkedList(){

    Date* date = new Date(2015,4,2);
    State* state = new State("NY");
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date, state);

    List<Person>* personList = new List<Person>();
    personList->addNode(person);

    ListNode<Person> *myPersonNode = personList->getHead();
    Person* myPerson = myPersonNode->getData();
    assert(myPerson->getLastName() == person->getLastName() );
    assert(*myPersonNode->getData() == *person );

    Person* newPerson = new Person("123", "FunTimes", "Ahead", date,state );
    personList->addNode(newPerson);

    ListNode<Person> *newPersonNode = personList->getTail();
    assert(*newPersonNode->getData() == * newPerson );
    assert(personList->getSize() == 2);

    Person* thirdPerson = new Person("1234", "MoreFunTimes", "WayAhead", date, state);
    personList->addNode(thirdPerson);
    assert(personList->getSize() == 3);

    personList->setEnforceUniqueItems(true);
    //Now i should not be able to re-insert "person"
    Person* myreturnedObject = personList->addNode(person);
    assert(*myreturnedObject == *person);
    assert(personList->getSize() == 3);

}


void testDatabase(string databaseLocation){

    Database* database = new Database();

    database->readfile(databaseLocation);
    //cout << "States: " << database->getStates()->getSize() << endl;

    /*
    int i = 0;
    List<State>* states = database->getStates();
    //ListNode<State> *head = states->getHead();
    ListNode<State> *currentHead = database->getStates()->getHead();
    while(currentHead){
        cout << "index: " << i << " " << currentHead->getData()->getState() << endl;
        i++;
        currentHead = currentHead->getNext();
    }*/

    //cout << "People: " << database->getPeople()->getSize() << endl;
    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);

    State *headState = database->getStates()->getHead()->getData();
    List<Person>* peopleInState = headState->getPeople();
    //cout << "State: " << headState->getState() << endl;
    ListNode<Person>* currentPerson = peopleInState->getHead();
    while(currentPerson){
        //cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
        assert(headState == currentPerson->getData()->getState());
        currentPerson = currentPerson->getNext();

    }
}

void testDateComparisonOperators(){

    Date* date1 = new Date("02021965");
    Date* date2 = new Date("24101947");
    Date* date3 = new Date("16061930");
    Date* date4 = new Date("13021922");

    assert(*date1 > *date2);
    assert(*date2 < *date1);
    assert(!(*date3 > *date2));
    assert(*date4 < *date1);

}

void testListFindNodeAndDatafunctions(string databaseLocation){

    //TODO: implement
    assert(false);
}

void testDeletionOfNodeInList(string databaseLocation){

    Database* database = new Database();
    database->readfile(databaseLocation);
    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);

   //database->states->de

}

void testMovePersonFunctionDatabase(string databaseLocation){
    Database* database = new Database();
    database->readfile(databaseLocation);

    int personIndex = 5;
    int oldStateIndex = 5;
    int newStateIndex = 6;

    Person* person = database->getPeople()->findNodeAtIndex(personIndex)->getData();
    ListNode<Person>* personNode = database->getPeople()->findNodeAtIndex(personIndex);
    person->printInfoInline();

    database->listStates();
    assert(database->getPeople()->indexForNode(personNode) == personIndex);

    State* oldState = database->getStates()->findNodeAtIndex(oldStateIndex)->getData();
    oldState->printInfo();
    State* newState = database->getStates()->findNodeAtIndex(newStateIndex)->getData();
    newState->printInfo();

    database->listPeopleInState(oldState->getState());
    database->listPeopleInState(newState->getState());

    database->movePerson(person->getSsn(), oldState->getState(), newState->getState());

    database->listPeopleInState(oldState->getState());
    database->listPeopleInState(newState->getState());
}


void testDatabaseDeletion(string databaseLocation){

    Database* database = new Database();

    database->readfile(databaseLocation);
    //cout << "States: " << database->getStates()->getSize() << endl;

    /*
    int i = 0;
    List<State>* states = database->getStates();
    //ListNode<State> *head = states->getHead();
    ListNode<State> *currentHead = database->getStates()->getHead();
    while(currentHead){
        cout << "index: " << i << " " << currentHead->getData()->getState() << endl;
        i++;
        currentHead = currentHead->getNext();
    }*/

    //cout << "People: " << database->getPeople()->getSize() << endl;
    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);

    State *headState = database->getStates()->getHead()->getData();
    List<Person>* peopleInState = headState->getPeople();
    cout << "State: " << headState->getState() << endl;
    ListNode<Person>* currentPerson = peopleInState->getHead();
    while(currentPerson){
        cout << "    - " << currentPerson->getData()->getLastName() << " "  << currentPerson->getData()->getState()->getState() << endl;
        assert(headState == currentPerson->getData()->getState());
        currentPerson = currentPerson->getNext();

    }


    delete database;
    database = new Database();

    database->readfile(databaseLocation);

    assert(database->getStates()->getSize() <= 51); // States should always be under 51 (including DC)
    assert(database->getPeople()->getSize() <= database->numberOfRecordsCounted);

    State *headState2 = database->getStates()->getHead()->getData();
    List<Person>* peopleInState2 = headState2->getPeople();
    cout << "State: " << headState2->getState() << endl;
    ListNode<Person>* currentPerson2 = peopleInState2->getHead();
    while(currentPerson2){
        cout << "    - " << currentPerson2->getData()->getLastName() << " "  << currentPerson2->getData()->getState()->getState() << endl;
        assert(headState2 == currentPerson2->getData()->getState());
        currentPerson2 = currentPerson2->getNext();
    }
}


vector<string> parseCommandString(string commandString){
    vector <string> arguments;

    string token;
    stringstream stringStream(commandString);

    while(getline(stringStream, token, ' ')){
        arguments.push_back(token);
    }

    if(arguments.size() == 0){
        arguments.push_back("ERROR");
    }
    return arguments;
}


COMMAND commandDetector(string s){


        //cout <<  s <<" is an operator "<<  endl;

    if(s == "exit" ){
        return EXIT_PROGRAM;
    }else if(s == "read" ){
        return READ;
    }else if(s == "states" ){
        return STATES;
    }else if(s == "list" ){
        return LIST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest"){
        return YOUNGEST;
    }else if (s == "oldest" ){
        return OLDEST;
    }else if (s == "youngest") {
        return YOUNGEST;
    }else if (s == "find" ){
        return FIND;
    }else if (s == "move") {
        return MOVE;
    }else if (s == "merge") {
        return MERGE;
    }else{
        //cout << "Error" << endl;
        return ERROR;
    }

}


void commandLineInterpreter(){

    cout << "Enter a command:" << endl;
    int command = 100;
    string commandString;
    Database* database;
    do{

        cout << "> ";
        std::getline(std::cin, commandString);
        vector<string> arguments = parseCommandString(commandString);
        COMMAND comm = commandDetector(arguments[0]);

        if(database == NULL && (comm != READ || comm != EXIT_PROGRAM)){
            cout << "Error: There must be a data present prior to running commands against the database." << endl;
        }else{
            switch (comm){
                case READ:
                    cout << "READING" << endl;
                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguements." << endl;
                        cout << "E.g. read /home/www/labs/152/dbfile1.txt" << endl;
                    }else{
                        database = new Database();
                        database->readfile(arguments[1]);
                        cout << "Reading Complete" << endl;
                    }

                    break;
                case STATES:

                    cout << "States" << endl;
                    if(arguments.size()>=2 ){
                        cout << "Error: Illegal number of arguments. This command takes one arguement." << endl;
                        cout << "E.g. states" << endl;
                    }else{
                        database->listStates();
                    }

                    break;
                case LIST:

                    cout << "List" << endl;

                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. list FL" << endl;
                    }else{
                        database->listPeopleInState(arguments[1]);
                    }

                    break;
                case OLDEST:

                    cout << "OLDEST" << endl;

                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. oldest NY" << endl;
                    }else{
                        database->findOldest(arguments[1]);
                    }

                    break;
                case YOUNGEST:
                    cout << "YOUNGEST" << endl;

                    if(arguments.size()>2 || arguments.size() == 1){
                        cout << "Error: Illegal number of arguments. This command takes two arguement." << endl;
                        cout << "E.g. youngest NY" << endl;
                    }else{
                        database->findYoungest(arguments[1]);
                    }

                    break;

                case FIND:
                    cout << "FIND" << endl;

                    if(arguments.size() != 3){
                        cout << "Error: Illegal number of arguments. This command takes three arguement." << endl;
                        cout << "E.g. find Larry Brown" << endl;
                    }else{
                        Person* person = database->findPerson(arguments[1], arguments[2]);
                        if(person){
                            cout << "  FOUND: " ;
                            person->printInfoInline();
                        }else{
                            cout << " -- " << arguments[1] << " " <<  arguments[2] << " is not in the list of people" << endl;
                        }
                    }

                    break;

                case MOVE:

                    cout << "MOVE" << endl;
                    //FIXME: Insert in social security order
                    if(arguments.size() != 4){
                        cout << "Error: Illegal number of arguments. This command takes four arguement." << endl;
                        cout << "E.g. move 108690448 KS MD" << endl;
                    }else{
                        database->movePerson(arguments[1], arguments[2], arguments[3]);
                    }

                    break;

                case MERGE:
                    cout << "merge" << endl;

                    if(arguments.size() != 4){
                        cout << "Error: Illegal number of arguments. This command takes four arguement." << endl;
                        cout << "E.g. merge NC SC CR" << endl;
                    }else{
                        database->mergeStates(arguments[1], arguments[2], arguments[3]);
                    }
                    break;
                case EXIT_PROGRAM:
                    command = 0;
                    cout << "EXITING" << endl;
                    break;

                case ERROR:
                    cout<< "Error: Illegal Syntax in command" << endl;


                default:
                    cout<< "Error: Illegal Syntax in command" << endl;
            }
        }

    }while(command != 0);
    cout << "Final EXIT" << endl;
}




int main() {
    cout << "Hello, World!" << endl;


    string testDatabaseLocation = "/Users/cj/Desktop/dbfile1.txt";
    testLinkedListSort();
    testDateClass();
    testDateComparisonOperators();
    testPersonClass();
    testStateClass();
    testLinkedList();
    testDatabase(testDatabaseLocation);
    //testDatabaseDeletion();
    //testMovePersonFunctionDatabase(testDatabaseLocation);
    commandLineInterpreter();

    return 0;
}