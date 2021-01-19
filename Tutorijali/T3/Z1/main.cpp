#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

int main() {
    
    srand(time(0));
    
    int n = 4;
    int limit = pow(n,2);
    
    int randomBroj = rand() % limit + 1;
    
    std::cout << randomBroj;
    
    return 0;
}