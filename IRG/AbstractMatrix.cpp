//
//  AbstractMatrix.cpp
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "AbstractMatrix.h"

//virtual IMatrix* nTranspose(bool);
//virtual IMatrix* nMultiply(IMatrix *);
//virtual double determinant();
//virtual IMatrix* subMatrix(int, int, bool);
//virtual IMatrix* nInvert();
//virtual double** toArray();
//virtual std::string toString();
//virtual std::string toString(int);
//virtual IVector* toVector(bool);

IMatrix* AbstractMatrix::add(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) + other->get(i, j);
            this->set(i, j, val);
        }
    }
    
    return this;
}

IMatrix* AbstractMatrix::nAdd(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) + other->get(i, j);
            mat->set(i, j, val);
        }
    }
    
    return mat;
}

IMatrix* AbstractMatrix::sub(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) - other->get(i, j);
            this->set(i, j, val);
        }
    }
    
    return this;
}

IMatrix* AbstractMatrix::nSub(IMatrix *other) {
    if(this->getRowsCount() != other->getRowsCount()
       || this->getColsCount() != other->getColsCount())
        throw "Incompatible operands";
    
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < this->getColsCount(); ++j) {
            double val = this->get(i, j) - other->get(i, j);
            mat->set(i, j, val);
        }
    }
    
    return mat;
}

