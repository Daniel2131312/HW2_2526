
#include "Utilities.h"
#include "Matrix.h"
#include <cmath>


Matrix::Matrix(const int n, const int m, const int init) {
    width = m >= 0 ? m : 0;
    length = n >= 0 ? n : 0;

    mat = new int[length * width];

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            (*this)(i, j) = init;
        }
    }
}

Matrix::Matrix() : width(0), length(0), mat(nullptr) {
}

Matrix::Matrix(const Matrix &matrix) : width(matrix.getWidth()), length(matrix.getLength()) {
    mat = new int[length * width];

    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < this->width; j++) {
            (*this)(i, j) = matrix(i, j);
        }
    }
}

Matrix::~Matrix() {
    delete[] this->mat;
}

int Matrix::getWidth() const {
    return this->width;
}

int Matrix::getLength() const {
    return this->length;
}

int &Matrix::operator()(int i, int j) {
    if (i < 0 || i >= length || j < 0 || j >= width) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return mat[i * width + j];
}

const int &Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= length || j < 0 || j >= width) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return mat[i * width + j];
}

Matrix Matrix::transpose() const {
    Matrix transpose(this->width, this->length);

    for (int i = 0; i < transpose.getLength(); i++) {
        for (int j = 0; j < transpose.getWidth(); j++) {
            transpose(i, j) = (*this)(j, i);
        }
    }

    return transpose;
}

Matrix &Matrix::operator+=(const Matrix &rightMat) {
    if (this->width != rightMat.getWidth() || this->length != rightMat.getLength()) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < this->width; j++) {
            (*this)(i, j) += rightMat(i, j);
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &rightMat) {
    return *this += (-rightMat);
}

Matrix &Matrix::operator*=(const Matrix &rightMat) {
    *this = *this * rightMat;
    return (*this);
}

Matrix Matrix::operator-() const {
    return *this * -1;
}

Matrix Matrix::operator*(int scalar) const {
    Matrix result(*this);

    return result *= scalar;
}

Matrix operator*(int scalar, const Matrix &mat) {
    return mat * scalar;
}

Matrix &Matrix::operator*=(int scalar) {
    for (int i = 0; i < this->length; i++) {
        for (int j = 0; j < this->width; j++) {
            (*this)(i, j) *= scalar;
        }
    }
    return *this;
}

double Matrix::CalcFrobeniusNorm(const Matrix &mat) {
    double sum = 0;

    for (int i = 0; i < mat.getLength(); i++) {
        for (int j = 0; j < mat.getWidth(); j++) {
            sum += mat(i, j) * mat(i, j);
        }
    }

    return sqrt(sum);
}

std::ostream &operator<<(std::ostream &stream, const Matrix &matrix) {
    if (matrix.getLength() == 0 || matrix.getWidth() == 0) {
        return stream;
    }

    for (int i = 0; i < matrix.getLength(); i++) {
        stream << '|';
        for (int j = 0; j < matrix.getWidth(); j++) {
            stream << matrix(i, j) << '|';
        }
        stream << '\n';
    }
    return stream;
}

Matrix Matrix::rotateClockwise() const {
    Matrix toRotate(this->transpose());

    for (int i = 0; i < toRotate.getLength(); i++) {
        for (int j = 0; j < toRotate.getWidth() / 2; j++) {
            int tmp = toRotate(i, j);
            toRotate(i, j) = toRotate(i, toRotate.getWidth() - j - 1);
            toRotate(i, toRotate.getWidth() - j - 1) = tmp;
        }
    }
    return toRotate;
}

Matrix Matrix::rotateCounterClockwise() const {
    return this->rotateClockwise().rotateClockwise().rotateClockwise();
}

Matrix &Matrix::operator=(const Matrix &toAssign) {
    if (this == &toAssign) {
        return *this;
    }

    int *mat = new int[toAssign.getLength() * toAssign.getWidth()];

    for (int i = 0; i < toAssign.getLength(); i++) {
        for (int j = 0; j < toAssign.getWidth(); j++) {
            mat[i * toAssign.getWidth() + j] = toAssign(i, j);
        }
    }

    delete[] this->mat;
    this->mat = mat;
    this->width = toAssign.getWidth();
    this->length = toAssign.getLength();

    return *this;
}

double Matrix::CalcDeterminant(const Matrix &mat) {
    if (mat.getLength() != mat.getWidth()) {
        exitWithError(MatamErrorType::NotSquareMatrix);
    }
    if (mat.getLength() == 1) {
        return mat(0, 0);
    }
    if (mat.getLength() == 0) {
        return 0;
    }

    double sum = 0;
    for (int i = 0; i < mat.getLength(); i++) {
        Matrix subMatrix = mat.getSubMatrixForDet(0, i);

        sum += (i % 2 ? -1 : 1) * mat(0, i) * CalcDeterminant(subMatrix);
    }
    return sum;
}

Matrix Matrix::getSubMatrixForDet(int rowToExclude, int colToExclude) const {
    Matrix subMatrix = Matrix(this->getLength() - 1, this->getWidth() - 1);

    for (int i = 0; i < this->getLength() - 1; i++) {
        for (int j = 0; j < this->getWidth() - 1; j++) {
            int k = i >= rowToExclude ? i + 1 : i;
            int l = j >= colToExclude ? j + 1 : j;
            subMatrix(i, j) = (*this)(k, l);
        }
    }
    return subMatrix;
}

bool operator==(const Matrix &leftMat, const Matrix &rightMat) {
    if (leftMat.getLength() != rightMat.getLength() || leftMat.getWidth() != rightMat.getWidth()) {
        return false;
    }

    int length = leftMat.getLength(), width = leftMat.getWidth();

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (leftMat(i, j) != rightMat(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix &leftMat, const Matrix &rightMat) {
    return !(leftMat == rightMat);
}

Matrix operator*(const Matrix &leftMat, const Matrix &rightMat) {
    if (leftMat.getWidth() != rightMat.getLength()) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(leftMat.getLength(), rightMat.getWidth());

    for (int i = 0; i < result.getLength(); i++) {
        for (int j = 0; j < result.getWidth(); j++) {
            for (int k = 0; k < leftMat.getWidth(); k++) {
                result(i, j) += leftMat(i, k) * rightMat(k, j);
            }
        }
    }
    return result;
}

Matrix operator+(const Matrix &leftMat, const Matrix &rightMat) {
    Matrix result(leftMat);
    result += rightMat;
    return result;
}

Matrix operator-(const Matrix &leftMat, const Matrix &rightMat) {
    return leftMat + (-rightMat);
}
