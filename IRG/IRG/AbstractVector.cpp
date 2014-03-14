//
//  AbstractVector.cpp
//  IRG
//
//  Created by Nino Uzelac on 14/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "AbstractVector.h"

IVector* AbstractVector::add(IVector *v) {
    for(int i = 0; i < v->getDimension(); ++i) {
        double sum = this->get(i) + v->get(i);
        this->set(i, sum);
    }
    
    return this;
}