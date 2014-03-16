//
//  AbstractMatrix.cpp
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "AbstractMatrix.h"

//virtual IMatrix* nTranspose(bool);
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

IMatrix* AbstractMatrix::nMultiply(IMatrix *other) {
    if(this->getColsCount() != other->getRowsCount())
        throw "Incompatible operands";
    
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    for(int i = 0; i < this->getRowsCount(); ++i) {
        for(int j = 0; j < other->getColsCount(); ++j) {
            double val = 0;
            for(int k = 0; k < this->getColsCount(); ++k) {
                val += this->get(i, k) * other->get(k, j);
            }
            mat->set(i, j, val);
        }
    }
    
    return mat;
}

double AbstractMatrix::determinant() {
    if(this->getColsCount() != this->getRowsCount())
        throw "Cannot calculate determinant for non-square matrix";
    
    double det = 0;
    if(this->getRowsCount() == 2) {
        det = this->get(0, 0) * this->get(1, 1)
              - this->get(0, 1) * this->get(1, 0);
    } else {
        int sign = 1;
        for(int j = 0; j < this->getColsCount(); ++j) {
            det += sign * this->get(0, j) * this->subMatrix(0, j, true)->determinant();
            sign = -sign;
        }
    }
    
    return det;
}


