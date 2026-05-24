#ifndef ALGORITHMS
#define ALGORITHMS

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <random>

void ImprimirMatriz(const std::vector<int>& M, int n) {
    for (int fila = 0; fila < n; fila++) {
        std::cout << "               ";
        for (int columna = 0; columna < n; columna++) {
            std::cout << M[fila * n + columna] << " ";
        }
        std::cout << '\n';
    }
}

std::vector<int> CrearMatrizAleatoriaCuadrada(int n) {
    std::vector<int> M(n * n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    for (int i = 0; i < n * n; i++) {
        M[i] = dist(gen);
    }

    return M;
}

std::vector<int> matrix_multiplication(
    const std::vector<int>& A, 
    const std::vector<int>& B,
    int n
){
    std::vector<int> C(n * n, 0); 

    for(int r = 0; r < n; r++){
        for(int k = 0; k < n; k++){
            int temp = A[r * n + k];
            for(int c = 0; c < n; c++){
                C[r * n + c] += temp * B[k * n + c];
            }
        }
    }
    return C;
}

std::vector<int> Suma(const std::vector<int>& A, const std::vector<int>& B) {
    std::vector<int> C(A.size());
    for(size_t i = 0; i < A.size(); i++){
        C[i] = A[i] + B[i];
    }  
    return C;
}

std::vector<int> Resta(const std::vector<int>& A, const std::vector<int>& B) {
    std::vector<int> C(A.size());
    for(size_t i = 0; i < A.size(); i++){
        C[i] = A[i] - B[i];
    }  
    return C;
}

std::vector<int> Strassen(
    const std::vector<int>& A,
    const std::vector<int>& B,
    int n
) {
    if (n == 1) { 
        std::vector<int> C(1);
        C[0] = A[0] * B[0];
        return C;
    }

    int m = n / 2;
    int m2 = m * m;

    std::vector<int> A11(m2), A12(m2), A21(m2), A22(m2); 
    std::vector<int> B11(m2), B12(m2), B21(m2), B22(m2); 

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            A11[i * m + j] = A[i * n + j];
            A12[i * m + j] = A[i * n + (m + j)];
            A21[i * m + j] = A[(m + i) * n + j];
            A22[i * m + j] = A[(m + i) * n + (m + j)];

            B11[i * m + j] = B[i * n + j];
            B12[i * m + j] = B[i * n + (m + j)];
            B21[i * m + j] = B[(m + i) * n + j];
            B22[i * m + j] = B[(m + i) * n + (m + j)];
        }
    }

    auto M1 = Strassen(Suma(A11, A22), Suma(B11, B22), m);
    auto M2 = Strassen(Suma(A21, A22), B11, m);
    auto M3 = Strassen(A11, Resta(B12, B22), m);
    auto M4 = Strassen(A22, Resta(B21, B11), m);
    auto M5 = Strassen(Suma(A11, A12), B22, m);
    auto M6 = Strassen(Resta(A21, A11), Suma(B11, B12), m);
    auto M7 = Strassen(Resta(A12, A22), Suma(B21, B22), m);

    std::vector<int> C(n * n); 

    for(int i = 0; i < m; i++){
        for(int j = 0; j < m; j++){
            C[i * n + j]             = M1[i * m + j] + M4[i * m + j] - M5[i * m + j] + M7[i * m + j];
            C[i * n + (m + j)]       = M3[i * m + j] + M5[i * m + j];
            C[(m + i) * n + j]       = M2[i * m + j] + M4[i * m + j];
            C[(m + i) * n + (m + j)] = M1[i * m + j] - M2[i * m + j] + M3[i * m + j] + M6[i * m + j];
        }
    }

    return C;
}

#endif