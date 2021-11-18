/**
 * EBNF Matriz Multiplication Expressions:
 * -
 * SecondPart = Line { Line } <EOF>
 * Line = Expression <CR>
 * Expression = Matrix | "(" Expression Expression ")"
 * Matrix = "A" | "B" | "C" | ... | "X" | "Y" | "Z"
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

struct matrix {
    int rows;
    int cols;
    long mults;
};

int     n, rows, cols, ptr;
char    c;
bool    error_flag;
matrix  m[255], final_result;
string  expr;


bool is_matrix(int i){ return ( 'A' <= expr[i] && expr[i] <= 'Z'); }
bool is_open(int i){   return (expr[i] == '('); }
bool is_close(int i){  return (expr[i] == ')'); }

int global_ptr;
bool parse_expr(matrix* result){

    if(is_matrix(global_ptr)){
        *result = m[expr[global_ptr]];
        global_ptr += 1;
        return true;

    } else if(is_open(global_ptr)){
        global_ptr += 1;

        matrix r1, r2;
        if(!parse_expr(&r1)) return false;
        if(!parse_expr(&r2)) return false;
        
        if(!is_close(global_ptr)) return false;
        global_ptr += 1;

        if(r1.cols != r2.rows) return false;
        
        r1.mults = (r1.rows * r1.cols * r2.cols) + r1.mults + r2.mults;
        r1.cols  = r2.cols;

        *result = r1;
        return true;       
    } 

    return false;
}


int main(void){
    expr.clear();

    // Lendo as matrizes
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> c >> rows >> cols;
        m[c].rows = rows;
        m[c].cols = cols;
        m[c].mults = 0; 
    }

    // Lendo a linha que o for acima não consome
    getline(std::cin, expr);

    // Lendo as expressoes
    while(getline(std::cin, expr)){
        // cout << expr << endl;
        global_ptr = 0;

        if(parse_expr(&final_result)){
            cout << final_result.mults << endl;
        } else {
            cout << "error" << endl;
        }
    }

    return 0;
}