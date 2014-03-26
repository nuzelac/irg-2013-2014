//
//  AbstractVector.h
//  IRG
//
//  Created by Nino Uzelac on 14/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__AbstractVector__
#define __IRG__AbstractVector__

#include "IVector.h"
#include <cmath>
#include <algorithm>
#include "MatrixVectorView.h"

class AbstractVector : public IVector {
public:
    virtual IVector* add(IVector*);
    virtual IVector* nAdd(IVector*);
    virtual IVector* sub(IVector*);
    virtual IVector* nSub(IVector*);
    virtual IVector* scalarMultiply(double);
    virtual IVector* nScalarMultiply(double);
    virtual double norm();
    virtual IVector* normalize();
    virtual IVector* nNormalize();
    virtual double cosine(IVector*);
    virtual double scalarProduct(IVector*);
    virtual IVector* nVectorProduct(IVector*);
    virtual IVector* nFromHomogeneus();
    virtual IMatrix* toRowMatrix(bool);
    virtual IMatrix* toColumnMatrix(bool);
    virtual double* toArray();
    virtual IVector* copyPart(int);
    virtual std::string toString();
    virtual std::string toString(int);
};

#endif /* defined(__IRG__AbstractVector__) */
