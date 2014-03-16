//
//  IVector.h
//  IRG
//
//  Created by Nino Uzelac on 14/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__IVector__
#define __IRG__IVector__

#include "IMatrix.h"

class IVector {
public:
    virtual int get(int) =0;
    virtual IVector* set(int, double) =0;
    virtual int getDimension() =0;
    virtual IVector* copy() =0;
    virtual IVector* copyPart(int) =0;
    virtual IVector* newInstance(int) =0;
    virtual IVector* add(IVector*) =0;
    virtual IVector* nAdd(IVector*) =0;
    virtual IVector* sub(IVector*) =0;
    virtual IVector* nSub(IVector*) =0;
    virtual IVector* scalarMultiply(double) =0;
    virtual IVector* nScalarMultiply(double) =0;
    virtual double norm() =0;
    virtual IVector* normalize() =0;
    virtual IVector* nNormalize() =0;
    virtual double cosine(IVector*) =0;
    virtual double scalarProduct(IVector*) =0;
    virtual IVector* nVectorProduct(IVector*) =0;
    virtual IVector* nFromHomogeneus() =0;
//    virtual IMatrix* toRowMatrix(bool) =0;
//    virtual IMatrix* toColumnMatrix(bool) =0;
    virtual double* toArray() =0;
};

#endif /* defined(__IRG__IVector__) */
