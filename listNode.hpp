//
// Created by cj on 4/2/15.
//

#ifndef SUEC2A4_LISTNODE_HPP
#define SUEC2A4_LISTNODE_HPP

#include <string>
using namespace std;

template<class Element>
class ListNode{
protected:
    Element* data;
    ListNode<Element>* next;
public:

    ListNode(){
        this->data = NULL;
        this->next = NULL;
    }

    ListNode(Element* data){
        this->data = data;
        this->next = NULL;
    }

    ListNode(Element* data, ListNode<Element>* next){
        this->data = data;
        this->next = next;
    }

    ~ListNode(){

    }


    void deleteWithData(){
        delete this->data;
        this->data == NULL;

        delete this->next;
        this->next == NULL;


    }

    void deleteWithoutData(){

        this->data == NULL;
        this->next->deleteWithoutData();
        delete this->next;
        this->next == NULL;

    }


    void setNext(ListNode<Element>* next){
        this->next = next;
    }
    void setData(Element* data){
        this->data = data;
    }

    ListNode<Element>* getNext(){
        return this->next;
    }

    Element* getData(){
        return this->data;
    }





};

#endif //SUEC2A4_LISTNODE_HPP
