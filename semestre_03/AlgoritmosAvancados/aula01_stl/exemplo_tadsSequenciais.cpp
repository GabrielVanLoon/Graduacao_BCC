/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01  Estudo de Containers Sequenciais
 * Ref.: https://en.cppreference.com/w/cpp/container
 */

/**
 * A Biblioteca Padrão do C++ (STL) implementa os seguintes conteiners 
 * sequenciais: 
 * 
 * <array>              static contiguous array
 * <vector>             dynamic contiguous array 
 * <deque>              double-ended queue 
 * <forward_list>       singly-linked list (Lista Encadeada)
 * <list>               doubly-linked list (Lista Duplamente Encadeada)
 */
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>

// Adicionais
#include <iostream>     // cin, cout
#include <algorithm>    // sort
#include <string> 

using namespace std;

int main(){
     
    /** 
     * array<Type T,size_t N>
     * Ref. https://en.cppreference.com/w/cpp/container/array
     */
        array<int, 5> arr = {3, 5, 2, 9, 0};

        for(int i = 0; i < arr.size(); i++)
            cout << arr[i] << " ";
        cout << endl;

        sort(arr.begin(), arr.end());

        for(int i = 0; i < arr.size(); i++)
            cout << arr[i] << " ";
        cout << endl << endl;

    /** 
     * vector<Type T>
     * Ref. https://en.cppreference.com/w/cpp/container/vector
     */
        vector<string> vet {"Olá,", "eu", "me", "chamo"};
        vet.push_back("Persa!");

        for(int i = 0; i < vet.size(); i++)
            cout << vet[i] << " ";
        cout << endl;

        cout << "O vector possui alocado atualmente " << vet.capacity() << " de memória" << endl;
        cout <<endl;

    /** 
     * deque<Type T>
     * Ref. https://en.cppreference.com/w/cpp/container/deque
     */
        deque<string> nomes {"Gabriel", "Christian", "Tamiris", "Albert"};

        nomes.push_front("Mathias");
        nomes.push_back("Giovanni");

        cout << "Members of the Gang:" << endl;
        while(!nomes.empty()){
            cout << nomes.front() << " ";
            nomes.pop_front();
        }
        cout << endl << endl;

    /** 
     * list<Type T>
     * Ref. https://en.cppreference.com/w/cpp/container/list
     */
        list<string> ls {"Algoritmos", "ICC2", "Física Básica"};

        ls.push_back("Cálculo II");
        ls.push_front("Matemática Discreta");

        cout << "Matérias 2º Semestre: " << endl;
        list<string>::iterator it = ls.begin();
        for(it = ls.begin(); it != ls.end(); it++)
            cout << *it << ", ";
        cout << endl << endl;

    /** 
     * foward_list<Type T>
     * Ref. https://en.cppreference.com/w/cpp/container/foward_list
     * When use foward_list? https://stackoverflow.com/questions/25472527/when-to-use-c-forward-list
     */
        forward_list<string> fls {"Cálculo I", "ICC I", "Lógica Digital"};

        // Não possui push_back pois não é duplamente encadeada.
        fls.push_front("Geometria Analítica");

        cout << "Matérias 1º Semestre: " << endl;
        forward_list<string>::iterator fit = fls.begin();
        for(fit = fls.begin(); fit != fls.end(); fit++)
            cout << *fit << ", ";
        cout << endl;

    return 0;
}