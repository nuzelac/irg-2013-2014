//
//  AbstractMatrix.h
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__AbstractMatrix__
#define __IRG__AbstractMatrix__

#include "IMatrix.h"
#include <string>

class AbstractMatrix : public IMatrix {
public:
    virtual IMatrix* nTranspose(bool);
    virtual IMatrix* add(IMatrix*);
    virtual IMatrix* nAdd(IMatrix*);
    virtual IMatrix* sub(IMatrix*);
    virtual IMatrix* nSub(IMatrix*);
    virtual IMatrix* nMultiply(IMatrix *);
    virtual double determinant();
    virtual IMatrix* subMatrix(int, int, bool);
    virtual IMatrix* nInvert();
    virtual double** toArray();
    virtual std::string toString();
    virtual std::string toString(int);
    virtual IVector* toVector(bool);
};

#endif /* defined(__IRG__AbstractMatrix__) */
