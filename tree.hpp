//
// Created by cj on 4/11/15.
//

#ifndef SUEC2A4_TREE_HPP
#define SUEC2A4_TREE_HPP




#include "treeNode.hpp"
#include <iostream>

using namespace std;

template<class Element>
class Tree{

protected:

    TreeNode<Element>* root;
    long size;
    bool enforceUniqueItems;

public:
    Tree(){
        this->root = NULL;
        this->size = 0;
        this->enforceUniqueItems = false;
    };

    Tree(TreeNode<Element>* root){
        this->root = root;
    }

    Tree(TreeNode<Element>* root, int size){
        this->root = root;
        this->size = size;
    }

    ~Tree(){
    }

    void deleteWithData(){
        if(this->root){
            delete this->root;
            this->root = NULL;
            this->size = 0;
        }
    }

    void deleteWithoutData(){
        if(this->root){
            this->root->deleteWithoutData();
            delete this->root;
            this->root = NULL;
            this->size = 0;
        }
    }

    Element* addNode(Element* data){
        TreeNode<Element>* newNode = new TreeNode<Element>(data);
        TreeNode<Element>* returnedNode = this->addNode(newNode);
        return returnedNode->getData();
    }


    TreeNode<Element>* addNode(TreeNode<Element>* node){

        //If every node must be unique, lets check for that. If we find a duplicate node, return that node, if not return the inserted node.
        //In other words, to avoid duplicates, lets return an existing node or the new node.
        if(this->enforceUniqueItems){
            TreeNode<Element>* myNode = this->isNodeInDataStructure(node);
            if(myNode) return myNode;
        }


        //TODO: Implement
        this->size++;
        return node;
    }

    //Setters and Getters
    void setRoot(TreeNode<Element>* node){
        this->root = node;
    }
    TreeNode<Element>* getRoot(){
        return this->root;
    }

    void setEnforceUniqueItems(bool enforcement){
        this->enforceUniqueItems = enforcement;
    }

    bool getEnforceUniqueItems(){
        return this->enforceUniqueItems;
    }

    TreeNode<Element>* getNode(int index){
        //check if index it out of bounds
        if(index >= this->size || index < 0){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }

        //TODO: determine if it is needed
        //it will never run this line
        return NULL;
    }

    int getSize(){
        return this->size;
    }



    TreeNode<Element>* isNodeInDataStructure(TreeNode<Element>* node){

        //TODO: implement

        //If the node is not found, return NULL.
        return NULL;
    }

    TreeNode<Element>* find(TreeNode<Element>* node){
        return this->isNodeInDataStructure(node);
    }

    /*
    ListNode<Element>* findNodeAtIndex(int index){
        if(index < 0 || index >= this->size){
            cout << "ERROR: Index is out of bounds" << endl;
            return NULL;
        }
        int currentIndex = 0;

        ListNode<Element>* myCurrentNode = this->root;
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
     */


    Element* findData(Element* data){

        //TODO: implement
        //If the node is not found, return NULL.
        return NULL;
    }

    //Helper function for finding and deleting data
    void findAndDeleteNode(Element* data){
        this->findAndDeleteNode(data, false);
    }

    //will find the ListNode but preserve the data in it but delete the
    void findAndDeleteNode(Element* data, bool preserveData){

        TreeNode<Element>* node = new TreeNode<Element>(data);
        TreeNode<Element>* newNode = this->find(node);
        //ListNode<Element>* node = this->find(new ListNode<Element>(data));
        this->deleteNode(node, preserveData);
    }

/*
    int indexForNode(TreeNode<Element>* node){
        int index = 0;
        ListNode<Element>* myCurrentNode = this->root;
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
*/
    void deleteNode(TreeNode<Element>* node){
        this->deleteNode(node, false);
    }

    void deleteNode(TreeNode<Element>* node, bool preserveData){

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
            TreeNode<Element>* headNode = this->getRoot();
            if(*node->getData() == *node->getData()){
                this->root->deleteNode(preserveData);
                delete this->root;
                this->root = NULL;

                this->size = 0;
                return;
            }else{
                cout << "Warning: nodes do match and cannot be removed" << endl;
                return;
            }
        }

        //TODO: implement

    }

/*
    void findAndDeleteNodePreserveData(){

    }



    void insertNode(Element* data){

    }

*/
    void sort(){

        //TODO: implement

    }


#endif //SUEC2A4_TREE_HPP
