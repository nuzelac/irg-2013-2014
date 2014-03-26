//
//  main.cpp
//  bibliotekaDemo
//
//  Created by Nino Uzelac on 26/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include <iostream>
#include "Vector.h"
#include "Matrix.h"

int main(int argc, const char * argv[])
{
    IVector *v1 = (Vector::parseSimple("2 3 -4"))->add(Vector::parseSimple("-1 4 -3"));
    printf("v1 = %s\n", v1->toString().c_str());
    
    IVector *s = v1->nAdd(Vector::parseSimple("-1 4 -3"));
    printf("s = %s\n", s->toString().c_str());
    
    IVector *v2 = v1->nVectorProduct(Vector::parseSimple("2 2 4"));
    printf("v2 = %s\n", s->toString().c_str());
    return 0;
}

