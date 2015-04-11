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
    }

    void deleteWithData(){
        if(this->head){
            delete this->head;
            this->head = NULL;
            this->tail = NULL;
            this->size = 0;
        }
    }

    void deleteWithoutData(){
        if(this->head){
            this->head->deleteWithoutData();
            delete this->head;
            this->head = NULL;
            this->tail = NULL;
            this->size = 0;
        }
    }

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


    //FIXME: Find way to reduce code
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

    ListNode<Element>* find(ListNode<Element>* node){
        return this->isNodeInList(node);
    }

    ListNode<Element>* findNodeAtIndex(int index){
        if(index < 0 || index >= this->size){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }
        int currentIndex = 0;

        ListNode<Element>* myCurrentNode = this->head;
        //FIXME: Can this be cleaned up?
        while(myCurrentNode){
            if(currentIndex == index){
                return myCurrentNode;
            }
            if(myCurrentNode->getNext() == NULL){
                return myCurrentNode;
            }else{
                currentIndex ++;
                myCurrentNode = myCurrentNode->getNext();
            }
        }
        return myCurrentNode;
    }



    Element* findData(Element* data){
        ListNode<Element>* currentNode = this->getHead();
        while(currentNode){ // While will keep iterating over the list until it is null
            if(*currentNode->getData() == *data){
                return currentNode;
            }else{
                currentNode = currentNode->getNext();
            }
        }
        //If the node is not found, return NULL.
        return NULL;
    }

    //Helper function for finding and deleting data
    void findAndDeleteNode(Element* data){
        this->findAndDeleteNode(data, false);
    }

    //will find the ListNode but preserve the data in it but delete the
    void findAndDeleteNode(Element* data, bool preserveData){

        ListNode<Element>* node = new ListNode<Element>(data);
        ListNode<Element>* newNode = this->find(node);
        //ListNode<Element>* node = this->find(new ListNode<Element>(data));
        this->deleteNode(node, preserveData);
    }


    int indexForNode(ListNode<Element>* node){
        int index = 0;
        ListNode<Element>* myCurrentNode = this->head;
        //FIXME: can it be reduced?
        while(myCurrentNode){
            if(*myCurrentNode->getData() == *node->getData()){
                return index;
            }
            if(myCurrentNode->getNext() == NULL){
                return index;
            }else{
                index ++;
                myCurrentNode = myCurrentNode->getNext();
            }
        }
        return index;
    }

    void deleteNode(ListNode<Element>* node){
        this->deleteNode(node, false);
    }

    void deleteNode(ListNode<Element>* node, bool preserveData){

        if(node == NULL){
            cout << "Warning: Node can not equal null when deleting a listNode" << endl;
            return;
        }

        //use case if there is no elements in the list
        if(this->size == 0){
            cout << "Warning: cannot remove node from empty list " << endl;
            return;
        }

        //use case if there is only one element in the list
        if(this->size == 1){
            ListNode<Element>* headNode = this->getHead();
            if(*node->getData() == *node->getData()){
                this->head->deleteNode(preserveData);
                delete this->head;
                this->head = NULL;
                this->tail = NULL;
                this->size = 0;
                return;
            }else{
                cout << "Warning: nodes do match and cannot be removed" << endl;
                return;
            }
        }

        //Check if the node being removed is the first element
        if(*node->getData() == *this->head->getData()){

            ListNode<Element>* temp = this->head->getNext();
            this->head->deleteNode(preserveData);
            delete this->head;
            this->head = temp;
            this->size--;
            return;
        }

        //Check if the node being removed is the last element
        if(*node->getData() == *this->tail->getData()){

            ListNode<Element>* temp = this->findNodeAtIndex(this->size - 2);
            this->tail->deleteNode(preserveData);
            delete this->tail;
            this->tail = temp;
            this->size--;
            this->tail->setNext(NULL);
            return;
        }

        //Use Case: If the item is in the middle, delete the node and set previous node to the "next" pointer of the next item of the node being deleted.
        int indexForNodeToDelete = this->indexForNode(node);

        //Get the NEXT  node
        ListNode<Element>*  myNextNode = this->findNodeAtIndex(indexForNodeToDelete + 1);
        //get the PREVIOUS  node
        ListNode<Element>*  myPreviousNode = this->findNodeAtIndex(indexForNodeToDelete - 1);
        myPreviousNode->setNext(myNextNode);

        this->size --;    //Decrement the number nodes
        node->deleteNode(preserveData);
        delete node;

    }

/*
    void findAndDeleteNodePreserveData(){

    }



    void insertNode(Element* data){

    }

*/
    void sort(){



    }





};

#endif //SUEC2A4_LIST_HPP
