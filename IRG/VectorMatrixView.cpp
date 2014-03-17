//
//  VectorMatrixView.cpp
//  IRG
//
//  Created by Nino Uzelac on 17/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "VectorMatrixView.h"

VectorMatrixView::VectorMatrixView(IMatrix *mat) {
    this->mat = mat;
    if(this->mat->getRowsCount() == 1)
        this->rowMatrix = true;
    else
        this->rowMatrix = false;
}

double VectorMatrixView::get(int i) {
    if(this->rowMatrix)
        return this->mat->get(0, i);
    else
        return this->mat->get(i, 0);
}

IVector* VectorMatrixView::set(int i, double val) {
    if(this->rowMatrix)
        this->mat->set(0, i, val);
    else
        this->mat->set(i, 0, val);
    
    return this;
}

int VectorMatrixView::getDimension() {
    if(this->rowMatrix)
        return this->mat->getColsCount();
    else
        return this->mat->getRowsCount();
}
