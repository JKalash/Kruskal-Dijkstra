//
//  Stack.h
//  Assignment 7
//
//  Created by Joseph Kalash on 11/29/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#ifndef __Assignment_7__Stack__
#define __Assignment_7__Stack__

#include <iostream>
#include "Vertex.h"
using namespace std;

class Node {
public:
    Vertex value;
    Node *next;                                                                  //Pointer to the next node in a stack
    Node(Vertex _v, Node *nextN = NULL) {                                        //Constructor that takes the residing properties as parameter
        value = _v;
        next = nextN;
    }
    Node(Node *nextN = NULL)  {next = nextN;}                                     //Constructor that only takes a pointer to the next node
    void print() const        {cout << value.city.name() << endl;}                //Prints the object encapsulated in the node
};

class Stack {
private:
    Node* head;                     //Pointer to the first node in the stack
    int size;                       //Number of nodes before the fence
    void init();                    //Initializes all properties
    void removeAll();               //Clear the entire list
    bool clear();
public:
    Stack();
    ~Stack();
    bool push(const Vertex&);     //Pushed a node with the desired element
    bool pop(Vertex *&);          //Pops the top node, after setting it to be the passed parameter
    bool peak(Vertex &) const;    //Sets the passed element to point to the element of the node pointed to by the fence
    void print() const;           //Prints the top element in the stack
    int getSize() const;          //Returns the number of nodes in the stack
    
};

#endif /* defined(__Assignment_7__Stack__) */
