//
//  AbstractVector.cpp
//  IRG
//
//  Created by Nino Uzelac on 14/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "AbstractVector.h"

IVector* AbstractVector::add(IVector *other) {
    if(this->getDimension() != other->getDimension())
        throw "Incompatible operands";
    
    for(int i = 0; i < this->getDimension(); ++i) {
        double add = this->get(i) + other->get(i);
        this->set(i, add);
    }
    
    return this;
}

IVector* AbstractVector::nAdd(IVector *other) {
    if(this->getDimension() != other->getDimension())
        throw "Incompatible operands";
    
    IVector *newVector = this->newInstance(this->getDimension());
    for(int i = 0; i < this->getDimension(); ++i) {
        double add = this->get(i) + other->get(i);
        newVector->set(i, add);
    }
    
    return newVector;
}

IVector* AbstractVector::sub(IVector *other) {
    if(this->getDimension() != other->getDimension())
        throw "Incompatible operands";
    
    for(int i = 0; i < this->getDimension(); ++i) {
        double sub = this->get(i) - other->get(i);
        this->set(i, sub);
    }
    
    return this;
}

IVector* AbstractVector::nSub(IVector *other) {
    if(this->getDimension() != other->getDimension())
        throw "Incompatible operands";
    
    IVector *newVector = this->newInstance(this->getDimension());
    for(int i = 0; i < this->getDimension(); ++i) {
        double sub = this->get(i) - other->get(i);
        newVector->set(i, sub);
    }
    
    return newVector;
}

IVector* AbstractVector::scalarMultiply(double val) {
    for(int i = 0; i < this->getDimension(); ++i) {
        double newVal = this->get(i) * val;
        this->set(i, newVal);
    }
    
    return this;
}

IVector* AbstractVector::nScalarMultiply(double val) {
    IVector *newVector = this->newInstance(this->getDimension());
    for(int i = 0; i < this->getDimension(); ++i) {
        double newVal = this->get(i) * val;
        newVector->set(i, newVal);
    }
    
    return newVector;
}

double AbstractVector::norm() {
    double sum = 0;
    for(int i = 0; i < this->getDimension(); ++i) {
        double val = this->get(i);
        sum += val * val;
    }
    
    return sqrt(sum);
}

