/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01  Estudo de E/S com C++
 */

/**
 * Biblioteca <iostream>
 * 
 * É a principal biblioteca de entrada e saída do C++ e possui
 * as principais Streams de comunicação do sistema. Sendo elas:
 * 
 * std::cin 	standard input
 * std::cout 	standard output
 * std::cerr 	standard error
 * std::clog 	standard log
 * std::wcin 	standard input
 * std::wcout 	standard output
 * std::wcerr 	standard error
 * std::wclog 	standard log 
 */ 
 #include <iostream>

 using namespace std;

 int main(){
     
    int idade;

    cout << "Digite a sua idade: ";
    cin >> idade;
    cout << "Você possui " << idade << " anos." << endl;

    return 0;
 }