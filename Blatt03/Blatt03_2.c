#include <stdio.h>
#include <stdlib.h>

double factorial(unsigned int n) //funktion für fakultät
{
    return n <= 1 ? 1 : n * factorial( n -1);
}

void main(){
    double e = 1;
    double eprev = 0;
    int i = 1;
    while(e != eprev){
        eprev = e;
        e= eprev + (1/factorial(i));
        printf("%d. %f\n", i, e);
        i++; 
    } 
}
