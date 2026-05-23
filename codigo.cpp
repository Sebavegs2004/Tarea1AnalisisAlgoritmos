#include <iostream>
#include <vector>
#include <random>

// Función para multiplicar matrices
std::vector<std::vector<int>> Suma(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    int n
) {
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    for(int filas = 0; filas < n; filas++){
        for(int columnas = 0; columnas < n; columnas++){
            C[filas][columnas] = A[filas][columnas] + B[filas][columnas];
        }
    }  
    return C;
}

std::vector<std::vector<int>> Resta(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    int n
) {
    std::vector<std::vector<int>> C(n, std::vector<int>(n));
    for(int filas = 0; filas < n; filas++){
        for(int columnas = 0; columnas < n; columnas++){
            C[filas][columnas] = A[filas][columnas] - B[filas][columnas];
        }
    }  
    return C;
}

void ImprimirMatriz(const std::vector<std::vector<int>>& M) {
    for (int fila = 0; fila < M.size(); fila++) {
        for (int columna = 0; columna < M[fila].size(); columna++) {
            std::cout << M[fila][columna] << " ";
        }
        std::cout << '\n';
    }
}

std::vector<std::vector<int>> CrearMatrizAleatoria(int filas, int columnas) {
    std::vector<std::vector<int>> M(filas, std::vector<int>(columnas));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            M[i][j] = dist(gen);
        }
    }

    return M;
}

std::vector<std::vector<int>> Strassen(
    const std::vector<std::vector<int>>& A,
    const std::vector<std::vector<int>>& B,
    int n
) {
    if (n == 1){
        std::vector<std::vector<int>> C(1, std::vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }
    int m;
    m = n / 2;

    std::vector<std::vector<int>> A11(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> A12(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> A21(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> A22(m, std::vector<int>(m)); 

    std::vector<std::vector<int>> B11(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> B12(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> B21(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> B22(m, std::vector<int>(m)); 

    for(int fila = 0; fila < m; fila++){
        for(int columna = 0; columna < m; columna++){
            A11[fila][columna] = A[fila][columna];
            A12[fila][columna] = A[fila][m + columna];
            A21[fila][columna] = A[m + fila][columna];
            A22[fila][columna] = A[m + fila][m + columna];
            B11[fila][columna] = B[fila][columna];
            B12[fila][columna] = B[fila][m + columna];
            B21[fila][columna] = B[m + fila][columna];
            B22[fila][columna] = B[m + fila][m + columna];
        }
    }

    auto M1 = Strassen(Suma(A11, A22, m), Suma(B11, B22, m), m);
    auto M2 = Strassen(Suma(A21, A22, m), B11, m);
    auto M3 = Strassen(A11, Resta(B12, B22, m), m);
    auto M4 = Strassen(A22, Resta(B21, B11, m), m);
    auto M5 = Strassen(Suma(A11, A12, m), B22, m);
    auto M6 = Strassen(Resta(A21, A11, m), Suma(B11, B12, m), m);
    auto M7 = Strassen(Resta(A12, A22, m), Suma(B21, B22, m), m);


    std::vector<std::vector<int>> C11(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> C12(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> C21(m, std::vector<int>(m)); 
    std::vector<std::vector<int>> C22(m, std::vector<int>(m)); 

    for(int filas = 0; filas < m; filas++){
        for(int columnas = 0; columnas < m; columnas++){
            C11[filas][columnas] = M1[filas][columnas] + M4[filas][columnas] - M5[filas][columnas] + M7[filas][columnas];
            C12[filas][columnas] = M3[filas][columnas] + M5[filas][columnas];
            C21[filas][columnas] = M2[filas][columnas] + M4[filas][columnas];
            C22[filas][columnas] = M1[filas][columnas] - M2[filas][columnas] + M3[filas][columnas] + M6[filas][columnas];
        }
    }

    std::vector<std::vector<int>> C(n, std::vector<int>(n)); 

    for(int filas = 0; filas < m; filas++){
        for(int columnas = 0; columnas < m; columnas++){
            C[filas][columnas] = C11[filas][columnas];
            C[filas][m + columnas] = C12[filas][columnas];
            C[m + filas][columnas] = C21[filas][columnas];
            C[m + filas][m + columnas] = C22[filas][columnas];
        }
    }

    return C;
}

int main() {
    auto A = CrearMatrizAleatoria(2, 2);
    auto B = CrearMatrizAleatoria(2, 2);

    ImprimirMatriz(A);
    ImprimirMatriz(B);

    auto C = Strassen(A, B, 2);

    ImprimirMatriz(C);
    return 0;
}