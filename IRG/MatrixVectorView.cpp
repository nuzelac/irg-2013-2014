//
//  MatrixVectorView.cpp
//  IRG
//
//  Created by Nino Uzelac on 17/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "MatrixVectorView.h"

MatrixVectorView::MatrixVectorView(IVector *original, bool asRowMatrix) {
    this->original = original;
    this->asRowMatrix = asRowMatrix;
}

int MatrixVectorView::getRowsCount() {
    return asRowMatrix ? 1 : this->original->getDimension();
}

int MatrixVectorView::getColsCount() {
    return asRowMatrix ? this->original->getDimension() : 1;
}

double MatrixVectorView::get(int i, int j) {
    if(asRowMatrix) {
        if(i != 0)
            throw "Index out of bounds";
        
        if(j < 0 || j >= this->getColsCount())
            throw "Index out of bounds";
        
        return this->original->get(j);
    } else {
        if(j != 0)
            throw "Index out of bounds";
        
        if(i < 0 || i >= this->getRowsCount())
            throw "Index out of bounds";
        
        return this->original->get(i);
    }
}

IMatrix* MatrixVectorView::set(int i, int j, double val) {
    if(i < 0 || i >= this->getRowsCount())
            throw "Index out of bounds";
    if(j < 0 || j >= this->getColsCount())
        throw "Index out of bounds";
    
    
    if(asRowMatrix) {
        this->original->set(j, val);
    } else {
        this->original->set(i, val);
    }
    
    return this;
}

IMatrix* MatrixVectorView::copy() {
    IMatrix *mat = this->newInstance(this->getRowsCount(), this->getColsCount());
    
    if(asRowMatrix) {
        for(int j = 0; j < this->getColsCount(); ++j)
            mat->set(0, j, this->get(0, j));
    } else {
        for(int i = 0; i < this->getRowsCount(); ++i)
            mat->set(i, 0, this->get(i, 0));
    }
    
    return mat;
}

IMatrix* MatrixVectorView::newInstance(int rows, int cols) {
    IMatrix *mat = new Matrix(rows, cols);
    
    return mat;
}