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

class AbstractVector : IVector {
public:
    AbstractVector();
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
};

#endif /* defined(__IRG__AbstractVector__) */
