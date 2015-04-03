#include <iostream>
#include "date.hpp"
#include "person.hpp"
#include "state.h"
#include "list.hpp"
#include "listNode.hpp"
#include <cassert>

using namespace std;


void testDateClass(){

    Date* date = new Date(2015,4,2);
    assert(date->getYear() == 2015);
    assert(date->getMonth() == 4);
    assert(date->getDay() == 2);
}

void testPersonClass(){
    Date* date = new Date(2015,4,2);
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date);

    assert(person->getSsn() == "00000000" );
    assert(person->getFirstName() == "MyFirstName" );
    assert(person->getLastName() == "MyLastName" );


}

void testStateClass(){

    State* newyork = new State("NY");
    State* newyork1 = new State("NY");
    State* newjersey = new State("NJ");

    assert( *newyork == *newyork1);
    assert( *newyork != *newjersey);


}

void testLinkedList(){

    Date* date = new Date(2015,4,2);
    Person* person = new Person("00000000", "MyFirstName", "MyLastName", date);

    List<Person>* personList = new List<Person>();
    personList->addNode(person);


    ListNode<Person> *myPersonNode = personList->getHead();
    Person* myPerson = myPersonNode->getData();
    assert(myPerson->getLastName() == person->getLastName() );
    assert(*myPersonNode->getData() == *person );

    Person* newPerson = new Person("123", "FunTimes", "Ahead", date);
    personList->addNode(newPerson);

    ListNode<Person> *newPersonNode = personList->getTail();
    assert(*newPersonNode->getData() == * newPerson );
    assert(personList->getSize() == 2);

    Person* thirdPerson = new Person("1234", "MoreFunTimes", "WayAhead", date);
    personList->addNode(thirdPerson);
    assert(personList->getSize() == 3);

    personList->setEnforceUniqueItems(true);
    //Now i should not be able to re-insert "person"
    Person* myreturnedObject = personList->addNode(person);
    assert(*myreturnedObject == *person);
    assert(personList->getSize() == 3);

}




int main() {
    cout << "Hello, World!" << endl;

    testDateClass();
    testPersonClass();
    testStateClass();
    testLinkedList();
    return 0;
}