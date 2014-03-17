//
//  MatrixSubMatrixView.h
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__MatrixSubMatrixView__
#define __IRG__MatrixSubMatrixView__

#include "AbstractMatrix.h"

class MatrixSubMatrixView : public AbstractMatrix {
private:
    int* rowIndexes;
    int rowIndexesSize;
    int* colIndexes;
    int colIndexesSize;
    IMatrix* mat;
    MatrixSubMatrixView(IMatrix*, int, int, int*, int*);
    
public:
    MatrixSubMatrixView(IMatrix*, int, int);
    virtual ~MatrixSubMatrixView();
    virtual int getRowsCount();
    virtual int getColsCount();
    virtual double get(int, int);
    virtual IMatrix* set(int, int, double);
    virtual IMatrix* copy();
    virtual IMatrix* newInstance(int, int);
    virtual IMatrix* subMatrix(int, int, bool);
};

#endif /* defined(__IRG__MatrixSubMatrixView__) */
