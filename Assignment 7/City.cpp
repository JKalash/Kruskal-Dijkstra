//
//  City.cpp
//  Assignment 7
//
//  Created by Joseph Kalash on 11/28/13.
//  Copyright (c) 2013 Joseph Kalash. All rights reserved.
//

#include "City.h"

City::City(string n, double lat, double lon) {
    setName(n);
    setLatLon(lat, lon);
}

void City::setLatLon(double lat, double lon) {
    this->lat = lat;
    this->lon = lon;
}

void City::setName(string n) {
    this->_n = n;
}
string City::name() const{
    return _n;
}
double City::latitude() {
    return this->lat;
}
double City::longitude() {
    return this->lon;
}

double City::getWeightWith(City c) {
    return sqrt((this->lat - c.latitude())*(this->lat - c.latitude()) + (this->lon - c.longitude())*(this->lon - c.longitude()));
}