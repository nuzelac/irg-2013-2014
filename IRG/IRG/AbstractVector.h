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

class AbstractVector : IVector {
public:
    AbstractVector();
    virtual IVector* add(IVector*);
};

#endif /* defined(__IRG__AbstractVector__) */
