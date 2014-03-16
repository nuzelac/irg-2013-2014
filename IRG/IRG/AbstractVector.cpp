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

IVector* AbstractVector::normalize() {
    double norm = this->norm();
    
    for(int i = 0; i < this->getDimension(); ++i) {
        double val = this->get(i) / norm;
        this->set(i, val);
    }
    
    return this;
}

IVector* AbstractVector::nNormalize() {
    double norm = this->norm();
    IVector *newVector = this->newInstance(this->getDimension());
    
    for(int i = 0; i < this->getDimension(); ++i) {
        double val = this->get(i) / norm;
        newVector->set(i, val);
    }
    
    return newVector;
}

double AbstractVector::cosine(IVector *other) {
    double cos = this->scalarProduct(other) / (this->norm() * other->norm());
    
    return cos;
}

double AbstractVector::scalarProduct(IVector *other) {
    if(this->getDimension() != other->getDimension())
        throw "Incompatible operands";

    double product = 0;
    for(int i = 0; i < this->getDimension(); ++i) {
        product += this->get(i) * other->get(i);
    }
    
    return product;
}

IVector* AbstractVector::nVectorProduct(IVector *other) {
    if(this->getDimension() != other->getDimension())
        throw "Incompatible operands";

    if(this->getDimension() != 3)
        throw "Vector product is defined for 3-dimensional vectors";
    
    IVector *newVector = this->newInstance(3);
    double valI = this->get(2) * other->get(3) - this->get(3) * other->get(2);
    double valJ = this->get(3) * other->get(1) - this->get(1) * other->get(3);
    double valK = this->get(1) * other->get(2) - this->get(2) * other->get(1);
    newVector->set(1, valI);
    newVector->set(2, valJ);
    newVector->set(3, valK);
    
    return newVector;
}

IVector* AbstractVector::nFromHomogeneus() {
    if(this->getDimension() < 2)
        throw "Incompatible vector";
    
    IVector *newVector = this->newInstance(this->getDimension() - 1);
    double homo = this->get(this->getDimension() - 1);
    
    for(int i = 0; i < this->getDimension()-1; ++i) {
        newVector->set(i, this->get(i) / homo);
    }
    
    return newVector;
}
