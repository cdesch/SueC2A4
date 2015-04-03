//
// Created by cj on 4/2/15.
//

#ifndef SUEC2A4_DATE_HPP
#define SUEC2A4_DATE_HPP


#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//This function converts a string to an integer
//It returns a variable of type int
int converStringToInt(string myString){
    //atoi() isn't something you would normally know about it
    //Documentation link http://www.cplusplus.com/reference/cstdlib/atoi/
    return atoi(myString.c_str());
}
//This function converts a string to an long
//It returns a variable of type long
//This function assumes that the string being converted is NOT a zero!!
long convertStringToLong(string myString){
    //Documentation Link http://www.cplusplus.com/reference/cstdlib/atol/
    long convertedNumber;
    convertedNumber = atol(myString.c_str());
    //Check if conversion failed
    if (convertedNumber == 0){
        cout << "***Error: Conversion to long Failed. Unicode bytes " << endl;
        cout << "***       detected in Data File." << endl;
        cout << "***Error Reading File. Remove Unicode Bytes in Data File." << endl;
        for (int i = 0; i < myString.length(); i++){
            //cout << i << ": " << myString[i] << " ";
            //If it is not a digit, remove it
            if (!isdigit(myString[i])){
                cout << " <--  ***** Not a integer *****"<< endl;
            }
        }
        //throw  "***Error Reading File. Remove Unicode Bytes from first line";
        string newString = myString.substr(3);
        convertedNumber = atol(newString.c_str());
    }
    return convertedNumber;
}


class Date {

private:
    int year;
    int month;
    int day;

public:
    //Constructor
    Date(); //Default Constructor
    Date(int y, int m, int d); //This is the constructor
    Date(string d); //Overloaded Constructor with accepting long date format
    //Deconstructor
    ~Date();

    //Member functions//
    void printInfo();

    //GETTERS//
    int getYear();
    int getMonth();
    int getDay();

    //SETTERS//
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
};

//Default Constructor
Date::Date(){
    this->year = 0;
    this->month = 0;
    this->day = 0;
}

//Constructor with params
Date::Date(int y, int m, int d){
    this->year = y;
    this->month = m;
    this->day = d;
}

Date::Date(string d){

    //Change from string to a long
    long dateValue = convertStringToLong(d);

    //break the dateValue into Year Month Day
    this->year = int(dateValue/10000);
    this->month = (dateValue/100) % 100;
    this->day = dateValue % 100;
}

//Deconstructor
Date::~Date(){
}

//Member Functions//
//YYYYMMDD Format
void Date::printInfo(){
    int zero = 0;
    printf("%d", year);
    if(month < 10) printf("%d", zero);
    printf("%d", month);
    if(day < 10) printf("%d", zero);
    printf("%d\n", day);
}

//GETTERS//
int Date::getYear(){
    return this->year;
}
int Date::getMonth(){
    return this->month;
}
int Date::getDay(){
    return this->day;
}

//SETTERS//
void Date::setYear(int y){
    this->year = y;
}
void Date::setMonth(int m){
    this->month = m;
}
void Date::setDay(int d){
    this->day = d;
}


#endif //SUEC2A4_DATE_HPP
