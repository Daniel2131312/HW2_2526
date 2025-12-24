
#include "MataMvidia.h"

#include <bits/ostream.tcc>
#include "Utilities.h"


MataMvidia::MataMvidia(const std::string &movieName, const std::string &author,
                       const Matrix *frames, int frameCount) {
    initializeMataMvidia(movieName, author, frames, frameCount);
}

MataMvidia::MataMvidia(const MataMvidia &toCopy) {
    initializeMataMvidia(toCopy.movieName, toCopy.author, toCopy.frames, toCopy.frameCount);
}

void MataMvidia::initializeMataMvidia(const std::string &movieName, const std::string &author,
                                      const Matrix *frames, int frameCount) {
    this->frameCount = frameCount >= 0 ? frameCount : 0;

    this->frames = new Matrix[this->frameCount];

    for (int i = 0; i < this->frameCount; i++) {
        this->frames[i] = Matrix(frames[i]);
    }
    this->movieName = movieName;
    this->author = author;
}

MataMvidia::~MataMvidia() {
    delete[] this->frames;
}

int MataMvidia::getFrameCount() const {
    return this->frameCount;
}

Matrix &MataMvidia::operator[](int frameInd) {
    if (frameInd < 0 || frameInd >= this->frameCount) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return frames[frameInd];
}

const Matrix &MataMvidia::operator[](int frameInd) const {
    if (frameInd < 0 || frameInd >= this->frameCount) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return frames[frameInd];
}

MataMvidia &MataMvidia::operator+=(const MataMvidia &toAdd) {
    for (int i = 0; i < toAdd.getFrameCount(); i++) {
        *this += toAdd.frames[i];
    }

    return *this;
}

MataMvidia &MataMvidia::operator+=(const Matrix &matrix) {
    Matrix *newFrames = new Matrix[++(this->frameCount)];

    for (int i = 0; i < (this->frameCount - 1); i++) {
        newFrames[i] = this->frames[i];
    }

    newFrames[this->frameCount - 1] = Matrix(matrix);
    delete[] this->frames;
    this->frames = newFrames;

    return *this;
}

MataMvidia operator+(const MataMvidia &leftMovie, const MataMvidia &rightMovie) {
    MataMvidia newMovie(leftMovie);

    newMovie += rightMovie;

    return newMovie;
}

std::ostream &operator<<(std::ostream &stream, const MataMvidia &movie) {
    stream << "Movie Name: " << movie.movieName << '\n';
    stream << "Author: " << movie.author << '\n' << std::endl;

    for (int frameInd = 0; frameInd < movie.frameCount; frameInd++) {
        stream << "Frame " << frameInd << ':' << '\n';

        stream << movie.frames[frameInd] << '\n';
    }
    stream << "-----End of Movie-----" << '\n';
    return stream;
}

MataMvidia &MataMvidia::operator=(const MataMvidia &toAssign) {
    if (this == &toAssign) {
        return *this;
    }

    Matrix *tmp = new Matrix[toAssign.getFrameCount()];

    for (int i = 0; i < toAssign.frameCount; i++) {
        tmp[i] = toAssign.frames[i];
    }

    this->movieName = toAssign.movieName;
    this->author = toAssign.author;
    this->frameCount = toAssign.frameCount;
    delete[] this->frames;
    this->frames = tmp;
    return *this;
}
