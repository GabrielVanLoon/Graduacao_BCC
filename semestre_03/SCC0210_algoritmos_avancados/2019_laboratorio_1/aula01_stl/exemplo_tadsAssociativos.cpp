/**
 * Turma de Algoritmos Avançados
 * Autor:   Gabriel Van Looon
 * Data:    Fev/2018
 * Aula 01  Estudo de Containers Associativos
 * Ref.: https://en.cppreference.com/w/cpp/container
 */

/**
 * A Biblioteca Padrão do C++ (STL) implementa os seguintes conteiners 
 * Associativos: 
 * 
 * <set>                collection of unique keys, sorted by keys 
 * <multiset>           collection of keys, sorted by keys
 * <map>                collection of key-value pairs, sorted by keys, keys are unique 
 * <multimap>           collection of key-value pairs, sorted by keys
 * 
 * Obs. Todas as estruturas acima ordenam os elementos a fim de otimizar
 * operações de acesso, inserção e busca. Além disso implementam seus dados
 * em uma esquema de Árvore Red-Black
 * 
 * Obs. No C++ foi introduzida a versão unordered_ de todas as estruturas acima. 
 * Em casos que a ordem dos dados não importa, é recomendado usar as versões
 * unorded_ devido à possibilidade de acesso de dados com custo O(1).
 */
#include <set> // Implementa ambos set e multiset
#include <map> // Implementa ambos map e multimap
#include <unordered_set>


// Adicionais
#include <iostream>     // cin, cout
#include <algorithm>    // sort
#include <string> 

using namespace std;

int main(){
     
    /** 
     * set<class Key>
     * Ref. https://en.cppreference.com/w/cpp/container/set
     * Obs. Geralmente implementado como uma Red-Black Tree
     * Obs. Não permite repetição de chaves.
     */
        set<int> s;
        set<int>::iterator sit;

        s.insert(1);
        s.insert(1);
        s.insert(5);
        s.insert(9);

        for(sit = s.begin(); sit != s.end(); sit++)
            // Todos aparecem 1 vez pois não há repetição.
            cout << "Elemento " << *sit << " aparece " << s.count(*sit) << " vez." << endl;
        cout << endl;

    /** 
     * multiset<class Key>
     * Ref. https://en.cppreference.com/w/cpp/container/multiset
     */
        multiset<int> ms;
        set<int>::iterator msit;

        ms.insert(1);
        ms.insert(1);
        ms.insert(1);
        ms.insert(5);
        ms.insert(9);

        // erase apaga o dado mesmo que tenha sido inserido mais de 1x
        // ms.erase(1);

        for(msit = ms.begin(); msit != ms.end(); msit++)
            cout << "Elemento " << *msit << " aparece " << ms.count(*msit) << "x." << endl;
        cout << endl;

    /** 
     * map<class Key, class Mapped_Type>
     * Ref. https://en.cppreference.com/w/cpp/container/map
     * Obs. Conjunto de chaves-valores. Implementada como uma Red-Black Tree
     */
        map<string, int> mp;
        map<string, int>::iterator mpit;

        mp["Ana"]    = 19;
        mp["Ana"]    = 27;
        mp["Josias"] = 22;
        mp.insert(pair<string,int>("Creuza",34));

        for(mpit = mp.begin(); mpit != mp.end(); mpit++)
            cout << mpit->first << " possui " << mpit->second << " anos." << endl;
        cout << endl;

     /** 
     * multimap<class Key, class Mapped_Type>
     * Ref. https://en.cppreference.com/w/cpp/container/multimap
     * Obs. Conjunto de chaves-valores. Implementada como uma Red-Black Tree
     */
        multimap<string, int> mmp;
        multimap<string, int>::iterator mmpit;

        mmp.insert(pair<string,int>("Ana",19));
        mmp.insert(pair<string,int>("Ana",27));
        mmp.insert(pair<string,int>("José",22));
        mmp.insert(pair<string,int>("Creuza",34));

        for(mmpit = mmp.begin(); mmpit != mmp.end(); mmpit++)
            cout << mmpit->first << " possui " << mmpit->second << " anos." << endl;
        cout << endl;

    /** 
     * unordered_multiset<class Key>
     * Ref. https://en.cppreference.com/w/cpp/container/multiset
     */
        unordered_multiset<int> ums;
        unordered_multiset<int>::iterator umsit;

        ums.insert(1);
        ums.insert(5);
        ums.insert(1);
        ums.insert(9);
        ums.insert(1);

        // Veja que a inserção dos dados não segue nenhum tipo de ordem
        // pois a posição dos dados depende de um hash gerado.
        for(umsit = ums.begin(); umsit != ums.end(); umsit++)
            cout << "Elemento " << *umsit << " aparece " << ums.count(*umsit) << "x." << endl;
        cout << endl;
        
    return 0;
}