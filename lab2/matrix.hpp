#ifndef STRASSEN_HPP
#define STRASSEN_HPP

#include <iostream>
#include <ostream>
template <typename T>
class MatrixOperator {
public:
    void Add(T** MatrixA, T** MatrixB, T** MatrixResult, int MatrixSize);
    void Sub(T** MatrixA, T** MatrixB, T** MatrixResult, int MatrixSize);
    // AssignMatrix - Assign Matrix B to Matrix A
    void AssignMatrix(T** MatrixA, T** MatrixB, int length);
    void GeneralMul(T** MatrixA, T** MatrixB, T** MatrixResult, int MatrixSize);
    void StrassenMatrixMul(int N, T** MatrixA, T** MatrixB, T** MatrixC, bool top = false);

    void PrintMatrix(std::ostream& os, T** MatrixA, int MatrixSize);

    T** GenerateMatrix(int N, T defaultVal);
};

template <typename T>
void MatrixOperator<T>::Add(T** MatrixA, T** MatrixB, T** MatrixResult, int MatrixSize) {
    for (int i = 0; i < MatrixSize; i++) {
        for (int j = 0; j < MatrixSize; j++) {
            MatrixResult[i][j] = MatrixA[i][j] + MatrixB[i][j];
        }
    }
}
template <typename T>
void MatrixOperator<T>::Sub(T** MatrixA, T** MatrixB, T** MatrixResult, int MatrixSize) {
    for (int i = 0; i < MatrixSize; i++) {
        for (int j = 0; j < MatrixSize; j++) {
            MatrixResult[i][j] = MatrixA[i][j] - MatrixB[i][j];
        }
    }
}
template <typename T>
void MatrixOperator<T>::GeneralMul(T** MatrixA, T** MatrixB, T** MatrixResult, int MatrixSize) {
    for (int i = 0; i < MatrixSize; i++) {
        for (int j = 0; j < MatrixSize; j++) {
            MatrixResult[i][j] = 0;
            for (int k = 0; k < MatrixSize; k++) {
                MatrixResult[i][j] = MatrixResult[i][j] + MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }
}

template <typename T>
void MatrixOperator<T>::StrassenMatrixMul(int N, T** MatrixA, T** MatrixB, T** MatrixC, bool top) {
    int HalfSize = N / 2;
    int newSize  = N / 2;

    if (N <= 8) {
        GeneralMul(MatrixA, MatrixB, MatrixC, N);
    } else {
        T** A11;
        T** A12;
        T** A21;
        T** A22;

        T** B11;
        T** B12;
        T** B21;
        T** B22;

        T** C11;
        T** C12;
        T** C21;
        T** C22;

        T** M1;
        T** M2;
        T** M3;
        T** M4;
        T** M5;
        T** M6;
        T** M7;
        T** AResult;
        T** BResult;

        // making a 1 diminsional pointer based array.
        A11 = new T*[newSize];
        A12 = new T*[newSize];
        A21 = new T*[newSize];
        A22 = new T*[newSize];

        B11 = new T*[newSize];
        B12 = new T*[newSize];
        B21 = new T*[newSize];
        B22 = new T*[newSize];

        C11 = new T*[newSize];
        C12 = new T*[newSize];
        C21 = new T*[newSize];
        C22 = new T*[newSize];

        M1 = new T*[newSize];
        M2 = new T*[newSize];
        M3 = new T*[newSize];
        M4 = new T*[newSize];
        M5 = new T*[newSize];
        M6 = new T*[newSize];
        M7 = new T*[newSize];

        AResult = new T*[newSize];
        BResult = new T*[newSize];

        int newLength = newSize;

        // making that 1 diminsional pointer based array , a 2D pointer based array
        for (int i = 0; i < newSize; i++) {
            A11[i] = new T[newLength];
            A12[i] = new T[newLength];
            A21[i] = new T[newLength];
            A22[i] = new T[newLength];

            B11[i] = new T[newLength];
            B12[i] = new T[newLength];
            B21[i] = new T[newLength];
            B22[i] = new T[newLength];

            C11[i] = new T[newLength];
            C12[i] = new T[newLength];
            C21[i] = new T[newLength];
            C22[i] = new T[newLength];

            M1[i] = new T[newLength];
            M2[i] = new T[newLength];
            M3[i] = new T[newLength];
            M4[i] = new T[newLength];
            M5[i] = new T[newLength];
            M6[i] = new T[newLength];
            M7[i] = new T[newLength];

            AResult[i] = new T[newLength];
            BResult[i] = new T[newLength];
        }
        // splitting input Matrixes, into 4 submatrices each.
        for (int i = 0; i < N / 2; i++) {
            for (int j = 0; j < N / 2; j++) {
                A11[i][j] = MatrixA[i][j];
                A12[i][j] = MatrixA[i][j + N / 2];
                A21[i][j] = MatrixA[i + N / 2][j];
                A22[i][j] = MatrixA[i + N / 2][j + N / 2];

                B11[i][j] = MatrixB[i][j];
                B12[i][j] = MatrixB[i][j + N / 2];
                B21[i][j] = MatrixB[i + N / 2][j];
                B22[i][j] = MatrixB[i + N / 2][j + N / 2];
            }
        }

        // calculate M1..7
        // M1[][]
        Add(A11, A22, AResult, HalfSize);
        Add(B11, B22, BResult, HalfSize);  // p5=(a+d)*(e+h)

        // now that we need to multiply this, we use the strassen itself.
        StrassenMatrixMul(HalfSize, AResult, BResult, M1);

        // TODO
        if (top) {
            PrintMatrix(std::cout, M1, HalfSize);
            std::cout << std::endl;
        }

        // M2[][]
        Add(A21, A22, AResult, HalfSize);               // M2=(A21+A22)B11   p3=(c+d)*e
        StrassenMatrixMul(HalfSize, AResult, B11, M2);  // Mul(AResult,B11,M2);

        // TODO
        if (top) {
            PrintMatrix(std::cout, M2, HalfSize);
            std::cout << std::endl;
        }

        // M3[][]
        Sub(B12, B22, BResult, HalfSize);               // M3=A11(B12-B22)   p1=a*(f-h)
        StrassenMatrixMul(HalfSize, A11, BResult, M3);  // Mul(A11,BResult,M3);

        // TODO
        if (top) {
            PrintMatrix(std::cout, M3, HalfSize);
            std::cout << std::endl;
        }

        // M4[][]
        Sub(B21, B11, BResult, HalfSize);               // M4=A22(B21-B11)    p4=d*(g-e)
        StrassenMatrixMul(HalfSize, A22, BResult, M4);  // Mul(A22,BResult,M4);

        // TODO
        if (top) {
            PrintMatrix(std::cout, M4, HalfSize);
            std::cout << std::endl;
        }

        // M5[][]
        Add(A11, A12, AResult, HalfSize);               // M5=(A11+A12)B22   p2=(a+b)*h
        StrassenMatrixMul(HalfSize, AResult, B22, M5);  // Mul(AResult,B22,M5);

        // TODO
        if (top) {
            PrintMatrix(std::cout, M5, HalfSize);
            std::cout << std::endl;
        }

        // M6[][]
        Sub(A21, A11, AResult, HalfSize);
        Add(B11, B12, BResult, HalfSize);                   // M6=(A21-A11)(B11+B12)   p7=(c-a)(e+f)
        StrassenMatrixMul(HalfSize, AResult, BResult, M6);  // Mul(AResult,BResult,M6);

        // TODO
        if (top) {
            PrintMatrix(std::cout, M6, HalfSize);
            std::cout << std::endl;
        }

        // M7[][]
        Sub(A12, A22, AResult, HalfSize);
        Add(B21, B22, BResult, HalfSize);                   // M7=(A12-A22)(B21+B22)    p6=(b-d)*(g+h)
        StrassenMatrixMul(HalfSize, AResult, BResult, M7);  // Mul(AResult,BResult,M7);

        // TODO
        if (top) {
            PrintMatrix(std::cout, M7, HalfSize);
            std::cout << std::endl;
        }

        // C11 = M1 + M4 - M5 + M7;
        Add(M1, M4, AResult, HalfSize);
        Sub(M7, M5, BResult, HalfSize);
        Add(AResult, BResult, C11, HalfSize);

        // C12 = M3 + M5;
        Add(M3, M5, C12, HalfSize);

        // C21 = M2 + M4;
        Add(M2, M4, C21, HalfSize);

        // C22 = M1 + M3 - M2 + M6;
        Add(M1, M3, AResult, HalfSize);
        Sub(M6, M2, BResult, HalfSize);
        Add(AResult, BResult, C22, HalfSize);

        // gather all submatrices to results
        for (int i = 0; i < N / 2; i++) {
            for (int j = 0; j < N / 2; j++) {
                MatrixC[i][j]                 = C11[i][j];
                MatrixC[i][j + N / 2]         = C12[i][j];
                MatrixC[i + N / 2][j]         = C21[i][j];
                MatrixC[i + N / 2][j + N / 2] = C22[i][j];
            }
        }

        // free all two-demension array
        for (int i = 0; i < newLength; i++) {
            delete[] A11[i];
            delete[] A12[i];
            delete[] A21[i];
            delete[] A22[i];

            delete[] B11[i];
            delete[] B12[i];
            delete[] B21[i];
            delete[] B22[i];
            delete[] C11[i];
            delete[] C12[i];
            delete[] C21[i];
            delete[] C22[i];
            delete[] M1[i];
            delete[] M2[i];
            delete[] M3[i];
            delete[] M4[i];
            delete[] M5[i];
            delete[] M6[i];
            delete[] M7[i];
            delete[] AResult[i];
            delete[] BResult[i];
        }
        delete[] A11;
        delete[] A12;
        delete[] A21;
        delete[] A22;
        delete[] B11;
        delete[] B12;
        delete[] B21;
        delete[] B22;
        delete[] C11;
        delete[] C12;
        delete[] C21;
        delete[] C22;
        delete[] M1;
        delete[] M2;
        delete[] M3;
        delete[] M4;
        delete[] M5;
        delete[] M6;
        delete[] M7;
        delete[] AResult;
        delete[] BResult;
    }
}

template <typename T>
void MatrixOperator<T>::AssignMatrix(T** MatrixA, T** MatrixB, int length) {
    for (int row = 0; row < length; row++) {
        for (int column = 0; column < length; column++) {
            MatrixA[row][column] = MatrixB[row][column];
        }
    }
}

template <typename T>
T** MatrixOperator<T>::GenerateMatrix(int N, T defaultVal) {
    T** matrix = new int*[N];
    for (int i = 0; i < N; ++i) {
        matrix[i] = new T[N];
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = defaultVal;
        }
    }
    return matrix;
}

template <typename T>
void MatrixOperator<T>::PrintMatrix(std::ostream& os, T** MatrixA, int MatrixSize) {
    for (int row = 0; row < MatrixSize; row++) {
        for (int column = 0; column < MatrixSize; column++) {
            os << MatrixA[row][column] << "\t";
            if ((column + 1) % ((MatrixSize)) == 0) os << std::endl;
        }
    }
    std::cout << std::endl;
}

#endif
