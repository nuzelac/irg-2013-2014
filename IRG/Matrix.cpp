//
//  Matrix.cpp
//  IRG
//
//  Created by Nino Uzelac on 17/03/14.
//  Copyright (c) 2014 Nino Uzelac. All rights reserved.
//

#include "Matrix.h"

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    
    this->elements = new double*[rows];
    for(int i = 0; i < rows; ++i) {
        elements[i] = new double[cols];
        
        for(int j = 0; j < cols; ++j) {
            elements[i][j] = 0;
        }
    }
}

Matrix::Matrix(int rows, int cols, double** arr, bool useArr) {
    this->rows = rows;
    this->cols = cols;
    
    if(useArr) {
        elements = arr;
    } else {
        this->elements = new double*[rows];
        for(int i = 0; i < rows; ++i) {
            elements[i] = new double[cols];
            
            for(int j = 0; j < cols; ++j) {
                elements[i][j] = arr[i][j];
            }
        }
    }
}

Matrix::~Matrix() {
    for(int i = 0; i < this->rows; ++i) {
        delete[] elements[i];
    }
    delete[] elements;
}

int Matrix::getRowsCount() {
    return this->rows;
}

int Matrix::getColsCount() {
    return this->cols;
}

double Matrix::get(int r, int c) {
    return this->elements[r][c];
}

IMatrix* Matrix::set(int r, int c, double val) {
    elements[r][c] = val;
    return this;
}

IMatrix* Matrix::copy() {
    IMatrix *mat = new Matrix(this->rows, this->cols, this->elements, false);
    
    return mat;
}

IMatrix* Matrix::newInstance(int rows, int cols) {
    return new Matrix(rows, cols);
}

Matrix* Matrix::parseSimple(std::string str) {
    std::string buf;
    std::stringstream ss(str);
    
    std::vector<double> tokens;
    
    int rowSize = -1;
    while (ss >> buf) {
        if(buf[0] == '|') {
            if(rowSize == -1) {
                rowSize = (int)tokens.size();
            }
        } else {
            tokens.push_back(atof(buf.c_str()));
        }
    }
    
    if(tokens.size() % rowSize != 0) {
        throw "Invalid input string";
    }
    
    int rows = (int)tokens.size() / rowSize;
    int cols = rowSize;
    
    double **elements = new double*[rows];
    for(int i = 0; i < rows; ++i) {
        elements[i] = new double[cols];
        
        for(int j = 0; j < cols; ++j) {
            elements[i][j] = tokens[i * cols + j];
        }
    }
    
    return new Matrix(rows, cols, elements, true);
}