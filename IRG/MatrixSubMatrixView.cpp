//
//  MatrixSubMatrixView.cpp
//  IRG
//
//  Created by Nino Uzelac on 16/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "MatrixSubMatrixView.h"

MatrixSubMatrixView::MatrixSubMatrixView(IMatrix *mat, int r, int c) {
    this->mat = mat;
    this->rowIndexesSize = this->getRowsCount()-1;
    this->rowIndexes = new int[this->rowIndexesSize];
    
    for(int i = 0, rowI = 0; i < this->rowIndexesSize; ++i) {
        if(i == r) continue;
        rowIndexes[rowI] = i;
        ++rowI;
    }
    this->colIndexesSize = this->getColsCount()-1;
    this->colIndexes = new int[this->colIndexesSize];

    for(int j = 0, colJ = 0; j < this->colIndexesSize; ++j) {
        if(j == c) continue;
        colIndexes[colJ] = j;
        ++colJ;
    }
}

MatrixSubMatrixView::MatrixSubMatrixView(IMatrix *mat, int rowsSize, int colsSize, int *rows, int *cols) {
    this->mat = mat;
    this->rowIndexes = rows;
    this->rowIndexesSize = rowsSize;
    this->colIndexes = cols;
    this->colIndexesSize = colsSize;
}

MatrixSubMatrixView::~MatrixSubMatrixView() {
    delete[] this->rowIndexes;
    delete[] this->colIndexes;
}

int MatrixSubMatrixView::getRowsCount() {
    return rowIndexesSize;
}

int MatrixSubMatrixView::getColsCount() {
    return colIndexesSize;
}

double MatrixSubMatrixView::get(int i, int j) {
    if(i < 0 || i >= this->rowIndexesSize
      || j < 0 || j >= this->colIndexesSize)
        throw "Index out of bounds";
    
    return this->mat->get(this->rowIndexes[i], this->colIndexes[j]);
}

IMatrix* MatrixSubMatrixView::set(int i, int j, double val) {
    if(i < 0 || i >= this->rowIndexesSize
       || j < 0 || j >= this->colIndexesSize)
        throw "Index out of bounds";
    
    return this->mat->set(this->rowIndexes[i], this->colIndexes[j], val);
}

IMatrix* MatrixSubMatrixView::copy() {
    IMatrix *mat = this->newInstance(this->rowIndexesSize, this->colIndexesSize);
    
    for(int i = 0; i < this->rowIndexesSize; ++i) {
        for(int j = 0; j < this->colIndexesSize; ++j) {
            mat->set(i, j, this->get(i, j));
        }
    }
    
    return mat;
}

IMatrix* MatrixSubMatrixView::newInstance(int i, int j) {
    return this->mat->newInstance(i, j);
}

IMatrix* MatrixSubMatrixView::subMatrix(int r, int c, bool isLive) {
    if(r < 0 || r >= this->rowIndexesSize
       || c < 0 || c >= this->colIndexesSize)
        throw "Index out of bounds";
    
    if(isLive) {
        int* rowIndexes = new int[this->rowIndexesSize-1];
        int* colIndexes = new int[this->colIndexesSize-1];
        
        for(int i = 0, rowI = 0; i < this->rowIndexesSize; ++i) {
            if(i == r) continue;
            rowIndexes[rowI] = this->rowIndexes[i];
            ++rowI;
        }

        for(int j = 0, colJ = 0; j < this->colIndexesSize; ++j) {
            if(j == c) continue;
            colIndexes[colJ] = this->colIndexes[j];
            ++colJ;
        }
        
        return new MatrixSubMatrixView(this->mat, this->rowIndexesSize-1, this->colIndexesSize-1, rowIndexes, colIndexes);
    } else {
        IMatrix *mat = this->newInstance(this->rowIndexesSize-1, this->colIndexesSize-1);
        
        for(int i = 0, rowI = 0; i < this->rowIndexesSize; ++i) {
            if(i == r) continue;
            
            for(int j = 0, colJ = 0; j < this->colIndexesSize; ++j) {
                if(j == c) continue;
                
                mat->set(rowI, colJ, this->mat->get(this->rowIndexes[i], this->colIndexes[j]));
                
                ++colJ;
            }
            
            ++rowI;
        }
        
        return mat;
    }
}
