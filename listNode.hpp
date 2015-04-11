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


    //Deletes node and data
    void deleteWithData(){

        if(this->data){
            delete this->data;
            this->data = NULL;
        }

    }

    void deleteCascading(bool preserveData){
        this->deleteNode(preserveData);
        if(this->next){
            this->next->deleteCascading(preserveData);
            delete this->next;
            this->next = NULL;
        }
    }

    void deleteNode(bool preserveData){

        if(preserveData){
            this->deleteWithoutData();
        }else{
            this->deleteWithData();
        }
    }

    //deletes node and preserves data
    void deleteWithoutData(){
        this->data = NULL;
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
