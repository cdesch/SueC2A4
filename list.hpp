//
// Created by cj on 4/2/15.
//

#ifndef SUEC2A4_LIST_HPP
#define SUEC2A4_LIST_HPP

#include "listNode.hpp"
#include <iostream>

using namespace std;

template<class Element>
class List{

protected:

    ListNode<Element>* head;
    ListNode<Element>* tail;
    long size;
    bool enforceUniqueItems;

public:
    List(){
        this->head = NULL;
        this->tail = NULL;
        this->size = 0;
        this->enforceUniqueItems = false;
    };

    List(ListNode<Element>* head){
        this->head = head;
        this->tail = this->getUnknownTail(head);
    }


    List(ListNode<Element>* head, ListNode<Element> *tail, int size){
        this->head = head;
        this->tail = tail;
        this->size = size;
    }
    ~List(){
        //TODO: Implement
    };


    Element* addNode(Element* data){
        ListNode<Element>* newNode = new ListNode<Element>(data);
        ListNode<Element>* returnedNode = this->addNode(newNode);
        return returnedNode->getData();
    }


    ListNode<Element>* getUnknownTail(ListNode<Element>* node){
        int i = 0;
        while(node->getNext() != NULL){
            node = node->getNext();
            i++;
        }
        this->size = i; //Reset our number of nodes since we didn't know what it was.
        return node;
    }

    ListNode<Element>* addNode(ListNode<Element>* node){

        //If every node must be unique, lets check for that. If we find a duplicate node, return that node, if not return the inserted node.
        //In other words, to avoid duplicates, lets return an existing node or the new node.
        if(this->enforceUniqueItems){
            ListNode<Element>* myNode = this->isNodeInList(node);
            if(myNode) return myNode;
        }

        //what if this is the first node to be added?
        if(this->head == NULL){
            //If head is ==  to NULL, it is the first node
            this->setHead(node);
            this->setTail(node);
        }else{
            //If it is not the first song, we can assume it needs to go on to the end
            //Check to see if the tail is equal to null
            if(this->tail == NULL){
                cout << "ERROR: Tail is empty :: Do something to fix it" << endl;
            }

            //Get the last SueLinkNode
            ListNode<Element>* lastNode = this->getTail();
            lastNode->setNext(node); //Set the newLastNode to next
            this->setTail(node); // New last node
        }
        this->size++;
        return node;
    }

    //Setters and Getters
    void setHead(ListNode<Element>* node){
        this->head = node;
    }
    ListNode<Element>* getHead(){
        return this->head;
    }
    void setTail(ListNode<Element>* node){
        this->tail = node;
    }
    ListNode<Element>* getTail(){
        return this->tail;
    }
    void setEnforceUniqueItems(bool enforcement){
        this->enforceUniqueItems = enforcement;
    }

    bool getEnforceUniqueItems(){
        return this->enforceUniqueItems;
    }

    ListNode<Element>* getNode(int index){
        //check if index it out of bounds
        if(index >= this->size || index < 0){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }

        //Check to see if the index is at the beginning or at the end.
        if(index == 0 ){
            return this->head;
        }else if (index == this->size-1){
            return this->tail;
        }

        ListNode<Element>* currentNode = this->head;
        for (int i = 0; i < this->size; i++) {
            if (index == i) {
                return currentNode;
            } else {
                currentNode = currentNode->getNext();
            }
        }
        //it will never run this line
        return currentNode;
    }

    int getSize(){
        return this->size;
    }

    ListNode<Element>* isNodeInList(ListNode<Element>* node){
        ListNode<Element>* currentNode = this->getHead();
        while(currentNode){ // While will keep iterating over the list until it is null
            if(*currentNode->getData() == *node->getData()){
                return currentNode;
            }else{
                currentNode = currentNode->getNext();
            }
        }
        //If the node is not found, return NULL.
        return NULL;
    }

};

#endif //SUEC2A4_LIST_HPP
