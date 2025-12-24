#pragma once

#include "Matrix.h"
#include <string>

using std::string;

class MataMvidia {
    int frameCount;
    Matrix *frames;
    std::string movieName;
    std::string author;

    void initializeMataMvidia(const std::string &movieName, const std::string &author,
                              const Matrix *frames, int frameCount);

public:
    MataMvidia(const std::string &movieName, const std::string &author,
               const Matrix *frames, int frameCount);

    MataMvidia(const MataMvidia &toCopy);

    ~MataMvidia();

    int getFrameCount() const;

    Matrix &operator[](int frameInd);

    const Matrix &operator[](int frameInd) const;

    MataMvidia &operator+=(const MataMvidia &toAdd);

    MataMvidia &operator+=(const Matrix &matrix);

    friend std::ostream &operator<<(std::ostream &stream, const MataMvidia &movie);

    MataMvidia &operator=(const MataMvidia &toAssign);
};

MataMvidia operator+(const MataMvidia &leftMovie, const MataMvidia &rightMovie);
