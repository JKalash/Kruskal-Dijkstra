//
//  Vertex.h
//  Assignment 7
//
//  Created by Joseph Kalash on 11/29/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#ifndef __Assignment_7__Vertex__
#define __Assignment_7__Vertex__

#include <iostream>
#include "City.h"
using namespace std;

class Vertex {
public:
    City city;
    bool wasVisited;
    Vertex() {};
    Vertex(City c) {city = c; wasVisited = false;}
    double getWeightToVertex(Vertex v) {return city.getWeightWith(v.city);}
    Vertex& operator=(const Vertex&v) {
        if(this == &v)
            return *this;
        city = v.city;
        return *this;
    }
};

#endif /* defined(__Assignment_7__Vertex__) */