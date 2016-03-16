//
//  Graph.h
//  Assignment 7
//
//  Created by Joseph Kalash on 11/28/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#ifndef __Assignment_7__Graph__
#define __Assignment_7__Graph__

#include <iostream>
#include <fstream>
#include <set>
#include <queue>
#include <algorithm>

#include "Vertex.h"
#include "Stack.h"
using namespace std;

class Graph {
private:
    int MAX_VERTICES = 2000;
    int nVertices;
    Vertex* vertexList;
    bool** adjacencyMatrix;
    int index(City c);
    Stack* stack;
public:
    Graph();
    int vertexCount();
    void addVertex(City c);
    void addEdge(int start, int end);
    void addEdge(City start, City end);
    void displayVertex(int v);
    int getAdjUnvisitedVertex(int v);
    void dfSearch();
    void writeToFile(string outName);
    void Kruskal(string outName);
    void Dijkestra(string outName, City source);
};


#endif /* defined(__Assignment_7__Graph__) */

