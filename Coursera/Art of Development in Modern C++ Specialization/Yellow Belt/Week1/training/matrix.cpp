#include <bits/stdc++.h>

using namespace std;

class Matrix {
public:
    Matrix() : Matrix(0, 0) {}

    Matrix(int rows_num, int cols_num) {
        Reset(rows_num, cols_num);
    }

    void Reset(int rows_num, int cols_num) {
        check_dimension(rows_num, cols_num);
        if (rows_num == 0 || cols_num == 0)
            rows_num = cols_num = 0;
        init_matrix(rows_num, cols_num);
    }

    int At(int row, int col) const {
        check_index(row, col);
        return matrix[row][col];
    }

    int &At(int row, int col) {
        check_index(row, col);
        return matrix[row][col];
    }

    int GetNumRows() const {
        return rows;
    }

    int GetNumColumns() const {
        return columns;
    }

    bool operator==(const Matrix &rhs) const {
        if (rows != rhs.rows || columns != rhs.columns)
            return false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (matrix[i][j] != rhs.At(i, j))
                    return false;
            }
        }
        return true;
    }

    Matrix operator+(const Matrix &rhs) const {
        if (rows != rhs.rows || columns != rhs.columns)
            throw invalid_argument("");
        Matrix result(rows, columns);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                result.At(i, j) = matrix[i][j] + rhs.At(i, j);
            }
        }
        return result;
    }

private:
    int rows;
    int columns;
    vector<vector<int>> matrix;

    void init_matrix(int rows_num, int cols_num) {
        rows = rows_num;
        columns = cols_num;
        matrix = vector<vector<int>>(rows, vector<int>(columns, 0));
    }

    void check_dimension(int rows_num, int cols_num) const {
        if (rows_num < 0 || cols_num < 0)
            throw out_of_range("");
    }

    void check_index(int row, int col) const {
        check_dimension(row, col);
        if (row >= matrix.size())
            throw out_of_range("");
        if (col >= matrix[row].size())
            throw out_of_range("");
    }
};

istream &operator>>(istream &stream, Matrix &mat) {
    int rows_num;
    int cols_num;
    stream >> rows_num >> cols_num;
    mat.Reset(rows_num, cols_num);
    for (int i = 0; i < rows_num; i++) {
        for (int j = 0; j < cols_num; j++) {
            stream >> mat.At(i, j);
        }
    }
    return stream;
}

ostream &operator<<(ostream &stream, const Matrix &mat) {
    stream << mat.GetNumRows() << " " << mat.GetNumColumns() << endl;
    for (int i = 0; i < mat.GetNumRows(); i++) {
        for (int j = 0; j < mat.GetNumColumns(); j++) {
            stream << mat.At(i, j);
            if (j + 1 != mat.GetNumColumns())
                stream << " ";
        }
        stream << endl;
    }
    return stream;
}