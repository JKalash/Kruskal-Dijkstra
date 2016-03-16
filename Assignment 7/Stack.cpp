//
//  Stack.cpp
//  Assignment 7
//
//  Created by Joseph Kalash on 11/29/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#include "Stack.h"

void Stack::init() {
    head = new Node(*new Vertex(), NULL);
    size = 0;
}

void Stack::removeAll() {
    for(int i=0; i<size; i++) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = NULL;
}

Stack::Stack() {
    init();
}

Stack::~Stack() {
    clear();
}

bool Stack::clear() {
    removeAll();
    init();
    return true;
}

bool Stack::push(const Vertex& s) {
    
    Node *newNode;
    if(size == 0)
        newNode = new Node(s, NULL);
    else newNode = new Node(s, head);
    
    head = newNode;
    size++;
    //cout << "Pushing ";
    //head->print();
    cout << endl;
    return true;
}

bool Stack::pop(Vertex *& st) {
    if(size==0) return false;
    
    st = &head->value;
    Node *temp = head;
    head = head->next;
    delete temp;
    size--;
    return true;
}

bool Stack::peak(Vertex & st) const {
    st = head->value;
    return true;
}

void Stack::print() const {
    head->print();
    cout << endl;
}

int Stack::getSize() const {
    return size;
}