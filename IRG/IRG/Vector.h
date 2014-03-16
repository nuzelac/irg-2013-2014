//
//  Vector.h
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#ifndef __IRG__Vector__
#define __IRG__Vector__

#include "AbstractVector.h"
#include <string>
#include <vector>
#include <sstream>

class Vector : public AbstractVector {
private:
    double* elements;
    int dimension;
    bool readOnly;
public:
    Vector(double*, int);
    Vector(bool, bool, double*, int);
    ~Vector();
    virtual double get(int);
    virtual IVector* set(int, double);
    virtual int getDimension();
    virtual IVector* copy();
    virtual IVector* newInstance(int);
    static Vector* parseSimple(std::string);
};

#endif /* defined(__IRG__Vector__) */
