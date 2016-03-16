//
//  City.h
//  Assignment 7
//
//  Created by Joseph Kalash on 11/28/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#ifndef __Assignment_7__City__
#define __Assignment_7__City__

#include <iostream>
#include <cmath>

using namespace std;

class City {
private:
    string _n;
    double lat;
    double lon;
public:
    City() {}
    City(string n, double lat, double lon);
    void setName(string n);
    void setLatLon(double lat, double lon);
    string name() const;
    double latitude();
    double longitude();
    double getWeightWith(City c);
};

#endif /* defined(__Assignment_7__City__) */
