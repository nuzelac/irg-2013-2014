//
//  Vector.cpp
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "Vector.h"

Vector::Vector(double *arr, int size) {
    this->readOnly = false;
    this->dimension = size;
    this->elements = new double[this->dimension];
    for(int i = 0; i < this->dimension; ++i) {
        this->elements[i] = arr[i];
    }
}

Vector::Vector(bool readOnly, bool useArr, double *arr, int size) {
    this->readOnly = readOnly;
    this->dimension = size;

    if(useArr) {
        this->elements = arr;
    } else {
        this->elements = new double[this->dimension];
        for(int i = 0; i < this->dimension; ++i) {
            this->elements[i] = arr[i];
        }        
    }
}

Vector::~Vector() {
    delete[] this->elements;
}

double Vector::get(int i) {
    if(i < 0 || i >= this->getDimension())
        throw "Index out of range";
    
    return this->elements[i];
}

IVector* Vector::set(int i, double val) {
    if(i < 0 || i >= this->getDimension())
        throw "Index out of range";
    if(this->readOnly)
        throw "Vector is immutable";
    
    this->elements[i] = val;

    return this;
}

int Vector::getDimension() {
    return this->dimension;
}

IVector* Vector::copy() {
    return new Vector(this->readOnly, false, this->elements, this->dimension);
}

IVector* Vector::newInstance(int dimension) {
    double *arr = new double[dimension];
    memset(arr, 0, dimension * sizeof(double));
    
    return new Vector(arr, this->dimension);
}

Vector* Vector::parseSimple(std::string str) {
    std::string buf;
    std::stringstream ss(str); // Insert the string into a stream
    
    std::vector<double> tokens; // Create vector to hold our words
    
    while (ss >> buf)
        tokens.push_back(atof(buf.c_str()));

    double *arr = new double[tokens.size()];
    
    for(int i = 0; i < tokens.size(); ++i) {
        arr[i] = tokens[i];
    }

    return new Vector(false, true, arr, (int)tokens.size());
}
