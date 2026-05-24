#include <iostream>
#include <vector>


#include "algorithms.cpp"

int main(int argc, char* argv[]){
    int n = std::stoi(argv[1]);
    auto A = CrearMatrizAleatoriaCuadrada(n);
    auto B = CrearMatrizAleatoriaCuadrada(n);

    auto C_clasico = matrix_multiplication(A,B, n);
    auto C_strassen = Strassen(A,B, A.size());

    ImprimirMatriz(A, n);
    ImprimirMatriz(B, n);

    ImprimirMatriz(C_clasico, n);
    ImprimirMatriz(C_strassen, n);
}