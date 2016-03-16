//
//  main.cpp
//  Assignment 7
//
//  Created by Joseph Kalash on 11/27/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Graph.h"

void createGraph(string fName, Graph* graph);

int main(int argc, const char * argv[])
{
    
    Graph* graph1 = new Graph();
    createGraph("cities2", graph1);
    graph1->Kruskal("cities2Kruskal.dot");
   
    Graph* graph2 = new Graph();
    createGraph("cities1.dot", graph2);
    
    graph1->Dijkestra("cities2Djikstra.dot", City("Bayrut", 33.89, 35.5));
    
    return 0;
}


void createGraph(string fName, Graph* graph) {
    
    ifstream infile;
    infile.open(fName+".txt");
    if(!infile.is_open())
        exit(-1);
    
    string garbage;
    infile >> garbage >> garbage >> garbage;
    
    
    while(infile) {
        string city = "";
        double lat(0), lon(0);
        
        infile >> city >> lon >> lat;
        
        if(city != "") {
            City c = City(city, lat, lon);
            graph->addVertex(c);
        }
    }
    
    //Fully connect the graph
    for(int i=0; i<graph->vertexCount()-1; i++)
        for(int j=i+1; j<graph->vertexCount(); j++)
            graph->addEdge(i, j);
    
    graph->writeToFile(fName+".dot");
}

