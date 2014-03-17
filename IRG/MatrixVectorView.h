//
//  MatrixVectorView.h
//  IRG
//
//  Created by Nino Uzelac on 17/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__MatrixVectorView__
#define __IRG__MatrixVectorView__

#include "AbstractMatrix.h"
#include "IVector.h"
#include "Matrix.h"

class MatrixVectorView : public AbstractMatrix {
private:
    bool asRowMatrix;
    IVector *original;
public:
    MatrixVectorView(IVector*, bool);
    virtual int getRowsCount();
    virtual int getColsCount();
    virtual double get(int, int);
    virtual IMatrix* set(int, int, double);
    virtual IMatrix* copy();
    virtual IMatrix* newInstance(int, int);
};

#endif /* defined(__IRG__MatrixVectorView__) */
