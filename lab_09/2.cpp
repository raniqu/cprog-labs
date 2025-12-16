#include "header.hpp"

void Construct(Matrix& out, size_t n, size_t m) {
    out.n_ = n;
    out.m_ = m;

    out.data_ = new int*[m];
    for (size_t i = 0; i < m; ++i) {
        out.data_[i] = new int[n]{};
    }
}

void Destruct(Matrix& in) {
    if (in.data_ == nullptr) return;
    for (size_t i = 0; i < in.m_; ++i) {
        delete[] in.data_[i];
    }
    delete[] in.data_;
    in.data_ = nullptr;
    in.n_ = 0;
    in.m_ = 0;
}

Matrix Copy(const Matrix& matrix) {
    Matrix result;
    result.n_ = matrix.n_;
    result.m_ = matrix.m_;

    if (matrix.data_ == nullptr) {
        result.data_ = nullptr;
        return result;
    }

    result.data_ = new int*[result.m_];
    for (size_t i = 0; i < result.m_; ++i) {
        result.data_[i] = new int[result.n_];
        for (size_t j = 0; j < result.n_; ++j) {
            result.data_[i][j] = matrix.data_[i][j];
        }
    }
    return result;

}

Matrix Add(const Matrix& a, const Matrix& b) {
    Matrix result;
    result.data_ = nullptr;
    if ((a.m_ != b.m_) || (a.n_ != b.n_)) {
        return result;
    }
    Construct(result, a.n_, b.n_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] + b.data_[i][j];
        }
    }
    return result;
}

Matrix Sub(const Matrix& a, const Matrix& b) {
    Matrix result;
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return result;
    }
    Construct(result, a.n_, b.n_);
    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {
            result.data_[i][j] = a.data_[i][j] - b.data_[i][j];
        }
    }
    return result;
}

Matrix Mult(const Matrix& a, const Matrix& b) {
    Matrix result;
    if (a.n_ != b.m_) {
        return result;
    }

    Construct(result, b.n_, a.m_);

    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < b.n_; ++j) {

            for (size_t k = 0; k < a.n_; ++k) {
                result.data_[i][j] += a.data_[i][k] * b.data_[k][j];
            }
        }
    }

    return result;
}

void Transposition(Matrix& matrix) {
    Matrix tran;
    tran.n_ = matrix.m_;
    tran.m_ = matrix.n_;

    tran.data_ = new int*[tran.m_];
    for (size_t i = 0; i < tran.m_; ++i) {
        tran.data_[i] = new int[tran.n_];
        for (size_t j = 0; j < tran.n_; ++j) {
            tran.data_[i][j] = matrix.data_[j][i];
        }
    }

    Destruct(matrix);
    matrix = tran;
}

bool operator==(const Matrix& a, const Matrix& b) {
    if (a.n_ != b.n_ || a.m_ != b.m_) {
        return false;
    }

    if (a.data_ == nullptr && b.data_ == nullptr) {
        return true;
    }

    for (size_t i = 0; i < a.m_; ++i) {
        for (size_t j = 0; j < a.n_; ++j) {

            if (a.data_[i][j] != b.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}