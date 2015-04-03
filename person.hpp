//
// Created by cj on 4/2/15.
//

#ifndef SUEC2A4_PERSON_HPP
#define SUEC2A4_PERSON_HPP

#include "date.hpp"

//**************************
//  Class Person
//**************************
class Person {

private:
    string lastName;
    string firstName;
    string ssn;
    Date* birthday;
    //State* state;

public:
    //Constructor
    Person(); //Default Constructor
    Person(string ssn, string firstName, string lastName, Date* birthday);
    Person(string ssn, string firstName, string lastName, string birthday);
    ~Person(); //Deconstructor

    //Member Functions//
    void printName();
    void printInfo(); //Print Name (first and last), SSN, Birthdate
    long age();     //Calculate the age of the person based on the birthdate

    //Setters and Getters

    //GETTERS//
    string getSsn() const;
    string getFirstName() const;
    string getLastName() const;
    Date* getBirthday() const;
    string getFullName(string fullname);

    //SETTERS//
    void setSsn(string ssn);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setBirthday(Date *birthday);      //Overloaded!!
    void setBirthday(string birthday);    //Overloaded!!
    void setFullName(string fullname);


    bool operator==(const Person& object){
        if(this->getLastName() == object.getLastName() &&
                this->getFirstName() == object.getFirstName() &&
                this->getSsn() == object.getSsn() &&
                this->getBirthday() == object.getBirthday()
                ){
            return true;
        }else{
            return false;
        }
    }

    bool operator!=(const Person& object){
        if(this->getLastName() == object.getLastName() &&
           this->getFirstName() == object.getFirstName() &&
           this->getSsn() == object.getSsn() &&
           this->getBirthday() == object.getBirthday()
                ){
            return false;
        }else{
            return true;
        }
    }
};
//Default Constructor
Person::Person(){

}

//Constructor with params
Person::Person(string ssn, string firstName, string lastName, Date* birthday){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = birthday;
}

Person::Person(string ssn, string firstName, string lastName, string birthday){
    this->ssn = ssn;
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthday = new Date(birthday);
}

//Deconstructor
Person::~Person(){
}

//Member Functions//
//Prints full name
void Person::printName(){
    printf("%s %s \n", firstName.c_str(), lastName.c_str());
}

void Person::printInfo(){
    printf("SSN: %s \n", ssn.c_str());
    printf("First Name: %s \n", firstName.c_str());
    printf("Last Name: %s \n", lastName.c_str());
    printf("Birthdate (YYYYMMDD): ");
    birthday->printInfo();  //Birthdate (YYYYMMDD): 20140914
}

long Person::age(){
    //This function computes the age to the nearest year.
    int age;
    age = 2014 - int(birthday->getYear());
    return age;
}

//Getters//
string Person::getSsn() const{
    return this->ssn; //Type of long
}
string Person::getFirstName() const{
    return this->firstName;
}
string Person::getLastName() const{
    return this->lastName;
}
Date* Person::getBirthday() const{
    return this->birthday;
}

//Setters//
void Person::setSsn(string ssn){
    this->ssn = ssn;
}
void Person::setFirstName(string firstName){
    this->firstName = firstName;
}
void Person::setLastName(string lastName){
    this->lastName = lastName;
}

//Overloading -- two different means to the same end.
void Person::setBirthday(Date* birthdate){
    this->birthday = birthdate;
}
void Person::setBirthday(string b){
    this->birthday = new Date(b);
}

#endif //SUEC2A4_PERSON_HPP
