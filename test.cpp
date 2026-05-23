#include <iostream>
#include <vector>


#include "algorithms.cpp"

int main(){
    std::vector<std::vector<int>> A = {
        {1, 2},
        {3, 4}
    };
    std::vector<std::vector<int>> B = {
        {1, 2},
        {3, 4}
    };

    std::vector<std::vector<int>> C_clasico(2, std::vector<int>(2));
    std::vector<std::vector<int>> C_strassen(2, std::vector<int>(2));

    C_clasico = matrix_multiplication(A,B);
    C_strassen = Strassen(A,B, A.size());

    std::vector <std::vector<int>> C = std::vector<std::vector<int>>{
        {7, 10},
        {15, 22}
    };
    
    if(C_clasico == C  && C_strassen == C){
        std::cout<<"Respuesta correcta"<<std::endl;
        return 0;
    }
}