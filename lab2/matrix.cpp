#include "matrix.hpp"

int main(int argc, char *argv[]) {
    MatrixOperator<int> m;

    int matrixSize = 16;

    auto matrixA = m.GenerateMatrix(matrixSize, 1);
    auto matrixB = m.GenerateMatrix(matrixSize, 1);

    auto matrixResult = m.GenerateMatrix(matrixSize, 0);

    m.StrassenMatrixMul(matrixSize, matrixA, matrixB, matrixResult, true);
    m.PrintMatrix(std::cout, matrixResult, matrixSize);
    m.GeneralMul(matrixA, matrixB, matrixResult, matrixSize);
    m.PrintMatrix(std::cout, matrixResult, matrixSize);
}