//
//  Graph.cpp
//  Assignment 7
//
//  Created by Joseph Kalash on 11/28/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#include "Graph.h"

bool operator<(const Vertex& lhs, const Vertex& rhs) {
    return lhs.city.name() < rhs.city.name();
}


Graph::Graph() {
    
    vertexList = new Vertex[MAX_VERTICES];
    
    adjacencyMatrix = new bool*[MAX_VERTICES];
    for(int i=0; i<MAX_VERTICES; i++)
        adjacencyMatrix[i] = new bool[MAX_VERTICES];
    
    nVertices = 0;
    
    for(int i=0; i<MAX_VERTICES; i++)
        for(int j=0; j<MAX_VERTICES; j++)
            adjacencyMatrix[i][j] = false;
    
    stack = new Stack();
}

int Graph::vertexCount() {
    return nVertices;
}

void Graph::addVertex(City c) {
    vertexList[nVertices++] = Vertex(c);
}

void Graph::addEdge(City start, City end) {
    int i = index(start);
    int j = index(end);
    
    if(i<0 || j<0) return;
    
    adjacencyMatrix[i][j] = adjacencyMatrix[j][i] = true;
}

void Graph::addEdge(int start, int end) {
    adjacencyMatrix[start][end] = true;
    adjacencyMatrix[end][start] = true; //This is not a directed graph
}
void Graph::displayVertex(int v) {
    cout << vertexList[v].city.name() << endl;
}

int Graph::index(City c) {
    for(int i=0; i<MAX_VERTICES; i++)
        if(vertexList[i].city.name() == c.name())
            return i;
    
    return -1; //Vertex not found
}

int Graph::getAdjUnvisitedVertex(int v) {
    for(int i=0; i<nVertices; i++)
        if(adjacencyMatrix[v][i] == 1 && !vertexList[i].wasVisited)
            return i;
    
    return -1; // No unvisited adjacent vertex found
}

void Graph::dfSearch() {
    vertexList[0].wasVisited = true;
    displayVertex(0);
    stack->push(vertexList[0]);
    while (stack->getSize()>0) {
        Vertex currentVertex;
        Vertex* vertexToPop;
        stack->peak(currentVertex);
        int v = 0;
        getAdjUnvisitedVertex(v);
        if(v == -1) //No vertex exists
            stack->pop(vertexToPop);
        else {
            currentVertex.wasVisited = true;
            displayVertex(v);
            stack->push(vertexList[v]);
        }
    }
    for(int i=0; i<nVertices; i++)
        vertexList[i].wasVisited = false;
}

void Graph::writeToFile(string outName) {
    ofstream outFile;
    outFile.open(outName);
    
    outFile << "Graph G {" << endl;
    
    //Write all vertices
    for(int i=0; i<nVertices; i++) {
        outFile << i << " [color = \"black\", label = \"" << vertexList[i].city.name() << "\"];" << endl;
    }
    
    cout.precision(7);
    //Write all edges
    for(int i=0; i<MAX_VERTICES; i++)
        for(int j=i; j<MAX_VERTICES; j++)
            if(adjacencyMatrix[i][j])
                outFile << j << "--" << i << " " << "[label = \"" << vertexList[i].getWeightToVertex(vertexList[j]) << "\"];" << endl;
    
    outFile << "}" << endl;
    outFile.close();
}

void Graph::Kruskal(string outName) {
    
    //Insert each vertex in a set and insert all sets in a dynamic array
    set<Vertex>* sets = new set<Vertex>[nVertices];
    for(int i=0; i<nVertices; i++) {
        set<Vertex> s;
        s.insert(vertexList[i]);
        sets[i] = s;
    }
    
    //Puch each edge in a priority queue
    struct Edge {
        int weight;
        int start;
        int end;
    };
    Edge* edges = new Edge[MAX_VERTICES*MAX_VERTICES];
    int nEdges = 0;
    for(int i=0; i<MAX_VERTICES-1; i++)
        for(int j=i; j<MAX_VERTICES; j++)
            if(adjacencyMatrix[i][j] == true) {
                Edge e;
                e.start = i;
                e.end = j;
                e.weight = vertexList[i].getWeightToVertex(vertexList[j]);
                edges[nEdges] = e;
                nEdges++;
            }
    
    //Now we need to sort the edges in increasing weight
    for(int i=0; i<nEdges; i++)
        for(int j=i; j<nEdges; j++)
            if(edges[i].weight > edges[j].weight) {
                //Swap edges
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
    
    //We now have all vertices in an array
    //And all edges structures, sorted by weight, in an array
    Edge* MST = new Edge[MAX_VERTICES*MAX_VERTICES];
    int nValidEdges = 0;
    
    for(int i=0; i<nEdges; i++) {
        Edge e = edges[i];
        Vertex start = vertexList[e.start];
        Vertex end = vertexList[e.end];
        if(sets[e.start].find(vertexList[e.end]) == sets[e.start].end()) { // The two vertices do not belong to the same set
           //Add the edge to our MST
            MST[nValidEdges] = e;
            nValidEdges++;
            //Get the union of vertex sets and insert it
            //in the corresponding place in the dynamic array
            set<Vertex> unionSet;
            set_union(sets[e.start].begin(), sets[e.start].end(), sets[e.end].begin(), sets[e.end].end(), inserter(unionSet, unionSet.begin()));
            sets[e.start] = unionSet;
        }
    }
    
    //We now have our MST
    //All we still need to do is output to file our resulting MST
    ofstream outputMST;
    outputMST.open(outName);
    
    outputMST << "Graph G {" << endl;
    //Write all vertices
    for(int i=0; i<nVertices; i++) {
        outputMST << i << " [color = \"black\", label = \"" << vertexList[i].city.name() << "\"];" << endl;
    }
    
    cout.precision(7);
    
    //Write our MST's edges
    for(int i=0; i<nValidEdges; i++) {
        Edge e = MST[i];
        outputMST << e.start << "--" << e.end << " " << "[label = \"" << e.weight << "\"];" << endl;
    }
    
    outputMST << "}" << endl;
    outputMST.close();
}


void Graph::Dijkestra(string outName, City source) {
    
    //STEP 1: SET ALL DISTANCES TO INFINITE
    int** distances = new int*[MAX_VERTICES];
    for(int i=0; i<MAX_VERTICES; i++)
        distances[i] = new int[MAX_VERTICES];
    
    for(int i=0; i<MAX_VERTICES; i++)
        for(int j=0; j<MAX_VERTICES; j++)
            distances[i][j] = pow(10, 6);
    
    // SET OUR SOURCE TO 0
    distances[index(source)][index(source)] = 0;
    
    //Create a priority queue containing all vertices. Call it Q
    priority_queue<Vertex, vector<Vertex>, less<Vertex>> Q;
    for(int i =0; i<nVertices; i++)
        Q.push(vertexList[i]);
    
    set<Vertex>* S = new set<Vertex>[nVertices];
    
    while(!Q.empty()) {
        Vertex u = Q.top();
        S->insert(u);
        for(int i=0; i<MAX_VERTICES; i++) {
            Vertex v = vertexList[i];
            if(adjacencyMatrix[index(u.city)][i])
                if(distances[index(source)][index(v.city)] > distances[index(source)][index(u.city)] + u.getWeightToVertex(v))
                    distances[index(source)][index(v.city)] = distances[index(source)][index(u.city)] + u.getWeightToVertex(v);
        }
        Q.pop();
    }

    //We now have our MST
    //All we still need to do is output to file our resulting MST
    ofstream outputMST;
    outputMST.open(outName);
    
    outputMST << "Graph G {" << endl;

    //Write all vertices
    for(int i=0; i<nVertices; i++) {
        outputMST << i << " [color = \"black\", label = \"" << vertexList[i].city.name() << "\"];" << endl;
    }
    
    cout.precision(7);
    
    for(int i=0; i<MAX_VERTICES; i++)
        for(int j=0; j<MAX_VERTICES; j++)
            if(distances[i][j] < pow(10, 6))
                outputMST << i << "--" << j << " " << "[label = \"" << distances[i][j] << "\"];" << endl;

    outputMST << "}" << endl;
    outputMST.close();
    
}

