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
        double sum = this->get(i) + other->get(i);
        this->set(i, sum);
    }
    
    return this;
}

IVector* AbstractVector::nAdd(IVector *other) {
    if(this->getDimension() != other->getDimension())
        throw "Incompatible operands";
    
    IVector *newV = this->newInstance(this->getDimension());
    for(int i = 0; i < this->getDimension(); ++i) {
        double sum = this->get(i) + other->get(i);
        newV->set(i, sum);
    }
    
    return newV;
}