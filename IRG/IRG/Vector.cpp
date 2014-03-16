//
//  Vector.cpp
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "Vector.h"

Vector::Vector(double *arr) {
    this->readOnly = false;
    this->dimension = sizeof(arr) / sizeof(double);
    this->elements = new double[this->dimension];
    for(int i = 0; i < this->dimension; ++i) {
        this->set(i, arr[i]);
    }
}

Vector::Vector(bool readOnly, bool useArr, double *arr) {
    this->readOnly = readOnly;
    this->dimension = sizeof(arr) / sizeof(double);

    if(useArr) {
        this->elements = arr;
    } else {
        for(int i = 0; i < this->dimension; ++i) {
            this->set(i, arr[i]);
        }        
    }
}

Vector::~Vector() {
    delete[] this->elements;
}

double Vector::get(int i) {
    if(i < this->getDimension() || i >= this->getDimension())
        throw "Index out of range";
    
    return this->elements[i];
}

IVector* Vector::set(int i, double val) {
    if(i < this->getDimension() || i >= this->getDimension())
        throw "Index out of range";
    
    this->elements[i] = val;

    return this;
}

int Vector::getDimension() {
    return this->dimension;
}

IVector* Vector::copy() {
    return new Vector(this->readOnly, false, this->elements);
}

IVector* Vector::newInstance(int dimension) {
    double *arr = new double[dimension];
    memset(arr, 0, dimension * sizeof(double));
    
    return new Vector(arr);
}
