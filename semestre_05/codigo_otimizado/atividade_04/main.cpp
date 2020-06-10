#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main(void){ 
    srand (time(NULL));

    std::cout << "Olarr" << std::endl;
    std::cout << "Olarr" << std::endl;
    std::cerr << (rand()%10 + 1) << std::endl;

    return 0;
}