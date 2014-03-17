//
//  VectorMatrixView.h
//  IRG
//
//  Created by Nino Uzelac on 17/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__VectorMatrixView__
#define __IRG__VectorMatrixView__

#include "AbstractVector.h"
#include "IVector.h"

class VectorMatrixView : public AbstractVector {
private:
    int dimension;
    bool rowMatrix;
    IMatrix* mat;
    
public:
    VectorMatrixView(IMatrix *);
    virtual double get(int);
    virtual IVector* set(int, double);
    virtual int getDimension();
    virtual IVector* copy();
    virtual IVector* newInstance(int);
};

#endif /* defined(__IRG__VectorMatrixView__) */
