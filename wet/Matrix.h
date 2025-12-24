#pragma once

#include <iostream>


class Matrix {
     int width;
     int length;
     int *mat;

     Matrix getSubMatrixForDet(int rowToExclude, int colToExclude) const;

public:
     Matrix(int n, int m, int init = 0);

     Matrix();

     Matrix(const Matrix &matrix);

     ~Matrix();

     int getWidth() const;

     int getLength() const;

     int &operator()(int i, int j);

     const int &operator()(int i, int j) const;

     Matrix transpose() const;

     Matrix operator-() const;

     Matrix &operator+=(const Matrix &mat2);

     Matrix &operator-=(const Matrix &mat2);

     Matrix &operator*=(const Matrix &mat2);

     Matrix operator*(int scalar) const;

     Matrix &operator*=(int scalar);

     static double CalcFrobeniusNorm(const Matrix &mat);

     Matrix rotateClockwise() const;

     Matrix rotateCounterClockwise() const;

     friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix);

     Matrix &operator=(const Matrix &other);

     static double CalcDeterminant(const Matrix &mat);
};

bool operator==(const Matrix &leftMat, const Matrix &rightMat);

bool operator!=(const Matrix &leftMat, const Matrix &rightMat);

Matrix operator*(const Matrix &leftMat, const Matrix &rightMat);

Matrix operator+(const Matrix &leftMat, const Matrix &rightMat);

Matrix operator-(const Matrix &leftMat, const Matrix &rightMat);

Matrix operator*(int scalar, const Matrix &mat);
