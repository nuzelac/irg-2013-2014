//
//  Matrix.h
//  IRG
//
//  Created by Nino Uzelac on 17/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__Matrix__
#define __IRG__Matrix__

#include "AbstractMatrix.h"

class Matrix : public AbstractMatrix {
private:
    double **elements;
    int rows;
    int cols;
public:
    Matrix(int, int);
    Matrix(int, int, double**, bool);
    virtual int getRowsCount();
    virtual int getColsCount();
    virtual double get(int, int);
    virtual IMatrix* set(int, int, double);
    virtual IMatrix* copy();
    virtual IMatrix* newInstance(int, int);
    static Matrix* parseSimple(std::string);
};

#endif /* defined(__IRG__Matrix__) */
