//
//  MatrixTransposeView.h
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__MatrixTransposeView__
#define __IRG__MatrixTransposeView__

#include "AbstractMatrix.h"

class MatrixTransposeView : public AbstractMatrix {
private:
    IMatrix* mat;
    
public:
    MatrixTransposeView(IMatrix*);
    virtual int getRowsCount();
    virtual int getColsCount();
    virtual double get(int, int);
    virtual IMatrix* set(int, int, double);
    virtual IMatrix* copy();
    virtual IMatrix* newInstance(int, int);
    virtual double** toArray();
};

#endif /* defined(__IRG__MatrixTransposeView__) */
