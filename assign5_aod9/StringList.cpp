// File Name: StringList.cpp
//
// Author: Andrew Daly
// Date: 04/22/2020
// Assignment Number: 5
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// This program is a functionality for a linked list of strings


//***********************************************************
//
// Created by Vlad on 4/12/2020.
//
//***********************************************************
#include <algorithm>
#include "StringList.h"

using namespace std;


StringList::StringList() : head(nullptr) {}

StringList::StringList(const vector<string>& stringVector) {
    if (stringVector.empty())
        this->head = nullptr;
    else {
        this->head = new StringNode(stringVector[0]);
        StringNode* node = this->head;
        for (int i = 1; i < stringVector.size(); ++i) {
            node->next = new StringNode(stringVector[i]);
            node = node->next;
        }
    }

}

void StringList::swapNodes(StringNode*& previousNext, StringNode* node1, StringNode* node2) {
    node1->next = node2->next;
    node2->next = node1;
    previousNext = node2;
}

void StringList::bubbleSort() {
    if (this->head == nullptr || this->head->next == nullptr)
        return;

    bool swapped;
    do {
        swapped = false;
        StringNode* prevNode = this->head;
        StringNode* currNode = this->head;

        // Handle case when we want to change the first node
        if (currNode->data > currNode->next->data) {
            StringList::swapNodes(this->head, currNode, currNode->next);
            swapped = true;
        }
        currNode = currNode->next;

        // Standard bubble sort, iterate until the end of list is reached, swap if out of order
        while (currNode->next != nullptr) {
            if (currNode->data > currNode->next->data) {
                // swap nodes
                StringList::swapNodes(prevNode->next, currNode, currNode->next);
                swapped = true;

                // because we have swapped currNode with the next one
                // so we don't need to update it like this currNode = currNode->next;
                prevNode = prevNode->next;
            }
            else {
                prevNode = prevNode->next;
                currNode = currNode->next;
            }
        }
    } while (swapped);
}

bool StringList::operator==(const StringList& other) {
    bool equal = true;
    StringNode* thisNode = this->head;
    StringNode* otherNode = other.head;

    while (thisNode != nullptr && otherNode != nullptr) {
        if (thisNode->data != otherNode->data) {
            equal = false;
            break;
        }
        thisNode = thisNode->next;
        otherNode = otherNode->next;
    }
    if (thisNode != nullptr || otherNode != nullptr)
        equal = false;
    return equal;
}

void StringList::pushBack(string s) {
    auto newNode = new StringNode(s);

    if (this->head == nullptr) {
        this->head = newNode;
    }
    else {
        StringNode* node = this->head;
        while (node->next != nullptr)
            node = node->next;
        node->next = newNode;
    }
}

void StringList::popBack() {
    if (this->head == nullptr) {
        // do nothing
    }
    else if (this->head->next == nullptr) {
        delete this->head;
        this->head = nullptr;
    }
    else {
        StringNode* node = this->head;
        while (node->next->next != nullptr)
            node = node->next;
        delete node->next;
        node->next = nullptr;
    }
}

string StringList::back() {
    string result;

    if (this->head != nullptr) {
        StringNode* node = this->head;
        for (; node->next != nullptr; node = node->next) {}
        result = node->data;
    }
    return result;
}


void StringList::swap(StringList& other) {
    std::swap(this->head, other.head);
}

StringList& StringList::operator=(StringList other) {
    this->swap(other);
    return *this;
}

//***********************************************************
//
// Created by Andrew Daly
//
//***********************************************************

//Function Definitions:

//***********************************************************
// StringList: copy constructor
//      other: other object
//    returns: list with different nodes that contain 
//             the same data
//***********************************************************

StringList::StringList(const StringList& other) {
   
   // if there is no other objects
   if(other.head == nullptr)
    {
        head = nullptr;
    }
   else
   {
       // setting head to equal other node's head
       head = new StringNode(other.head->data);
       // creating nodes to hold current and other's head
       StringNode* nodePtr = head, * otherNodePtr = other.head, * currentNode = other.head;

       while (currentNode->next != nullptr)
       {
           nodePtr->next = new StringNode(currentNode->next->data);
           currentNode = currentNode->next;
           nodePtr = nodePtr->next;
       }
   }
}

//***********************************************************
// ~StringList: a destructor, delete all nodes 
//              in the linked list
//***********************************************************

StringList::~StringList()
{
    StringNode* currentNode = head;
    while (currentNode != 0) {
        StringNode* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    head = 0;
}

//***********************************************************
// concatenate: concatenate all the strings
//   separator: string to be inserted each other string
//     returns: string all together
//***********************************************************

std::string StringList::concatenate(const std::string& separator) {
    
    string linkedStr = "";
    StringNode* node = head;

    if (node == nullptr) {
        // do nothing
    }
    while (node->next != nullptr) {
        // continually add given string as
        // long the next node is not NULL
        linkedStr += node->data + separator;
        node = node->next;
    }
    linkedStr += node->data;
    return linkedStr;
}

//***********************************************************
// toString: put one or more strings into a single string
//  returns: string with one or more given strings
//***********************************************************

std::string StringList::toString() {
    
    string singleStr = "";
    StringNode* node = head;

    if (head == nullptr) {
        // do nothing
    }
    while (node->next != nullptr) {
        // continually add string from the
        // linked list as long the next node
        // is not NULL
        singleStr += node->data + "\n";
        node = node->next;
    }
    singleStr += node->data;
    return singleStr;
}

//***********************************************************
// pushFront: put a given string to the beginning of the
//            linked list
//         s: given string
//***********************************************************

void StringList::pushFront(string s) {

    // making new node, setting it to be the given string
    auto firstNode = new StringNode(s);

    if (head == nullptr) {
        head = firstNode;
    }
    else {
        StringNode* node = head;
        head = firstNode;
        head->data = s;
        head->next = node;
    }
}

//***********************************************************
// popFront: remove a string from the beginning of
//           the linked list
//***********************************************************

void StringList::popFront() {
    
    if (head == nullptr) {
        // do nothing
    }
    else if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        StringNode* firstNode = head;
        head = head->next;
        delete firstNode;
    }
}

//***********************************************************
//   front: return a first value (string) in the linked list
// returns: first value (string) or empty string if the
//          the linked list is empty
//***********************************************************

string StringList::front() {
    
    string firstStr;
    if (head == nullptr) {
        firstStr = "";
    }
    else if (head != nullptr) {
        StringNode* firstNode = head;
        firstStr = firstNode->data;
    }
    return firstStr;
}

//***********************************************************
// operator+: create a new linked list containing elements of
//            both given linked list and other linked list
//      other: other linked list
//    returns: linked list combined of those linked lists
//***********************************************************

StringList StringList::operator+(const StringList& other) {
    
    
    StringNode* newHead, * thisNode = head, * otherNode = other.head;
    
    if (thisNode == nullptr && otherNode == nullptr)
        newHead = nullptr;
    else if (thisNode == nullptr) {
        newHead = new StringNode(otherNode->data);
        otherNode = otherNode->next;
    }
    else if (otherNode == nullptr) {
        newHead = new StringNode(thisNode->data);
        thisNode = thisNode->next;
    }
    else {
        newHead = new StringNode(thisNode->data);
        thisNode = thisNode->next;
        otherNode = otherNode;
    }
    StringNode* newNode = newHead;
    while (thisNode != nullptr) {
        newNode->next = new StringNode(thisNode->data);
        newNode = newNode->next;
        thisNode = thisNode->next;
    }
    while (otherNode != nullptr) {
        newNode->next = new StringNode(otherNode->data);
        newNode = newNode->next;
        otherNode = otherNode->next;
    }
    StringList newList;
    newList.head = newHead;
    return newList;
}

//***********************************************************
// reverse: reverse an order of the nodes in the linked list
//***********************************************************

void StringList::reverse() {

    if (head == nullptr) {
        // do nothing
    }

    // creating nodes to hold current and other's head
    StringNode* prevNode = nullptr, * currentNode = nullptr, * nextNode = nullptr;
    currentNode = head;
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    // now let the head point at the last node (prevNode)
    head = prevNode;
}

//***********************************************************
//   insert: insert the given string at nth position
//        s: string to be inserted
// position: index
//  returns: true if a specific condition is satisfied
//           otherwise return false
//***********************************************************

bool StringList::insert(std::string s, int position)
{
    bool ping = true;

    StringNode* Insertednode = new StringNode(s);
    Insertednode->next = nullptr;

    if (head == nullptr && position == 0) {
        head = Insertednode;
        return ping;
    }
    else if (head == nullptr && position > 0) {
        ping = false;
        return ping;
    }
    else if (position < 0) {
        ping = false;
        return ping;
    }
    else if (position == 0) {
        Insertednode->next = head;
        head = Insertednode;
        return ping;
    }
    StringNode* tempCurrentNode = head, * tempPreviousNode = nullptr;
    int index = 0;
    while (index < position) {
        tempPreviousNode = tempCurrentNode;
        tempCurrentNode = tempCurrentNode->next;
        index = index + 1;
    }
    Insertednode->next = tempCurrentNode;
    tempPreviousNode->next = Insertednode;

    return ping;
}

//***********************************************************
//   remove: removes a node at given nth position
// position: index
//  returns: true if a specific condition is satisfied
//           otherwise return false
//***********************************************************

bool StringList::remove(int position)
{
    bool equal = true;

    if (head == NULL)
    {
        equal = false;
        return equal;
    }
    // temp to store head
    StringNode* temp = head;

    if (position == 0)
    {
        head = temp->next;
        // delete temp
        free(temp);
        return equal;
    }
    // store previous of to be deleted node
    for (int i = 0; temp != NULL && i < position - 1; i++)
    {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL)
    {
        equal = false;
        return equal;
    }
    //delete node at position (next of position-1)
    StringNode* next = temp->next->next;
    free(temp->next);
    temp->next = next;
    
    return equal;
}
