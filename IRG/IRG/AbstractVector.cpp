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
    
    IVector *newV = this->newInstance(this->getDimension());
    for(int i = 0; i < this->getDimension(); ++i) {
        double add = this->get(i) + other->get(i);
        newV->set(i, add);
    }
    
    return newV;
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
    
    IVector *newV = this->newInstance(this->getDimension());
    for(int i = 0; i < this->getDimension(); ++i) {
        double sub = this->get(i) - other->get(i);
        newV->set(i, sub);
    }
    
    return newV;
}