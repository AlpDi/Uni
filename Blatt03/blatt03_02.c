#include <stdio.h>
#include <stdlib.h>

double factorial(unsigned int n) 
{
    return n <= 1 ? 1 : n * factorial(n -1);
}

double doublefactorial(unsigned int n)
{
    return n <= 1 ? 1 : n * doublefactorial(n -2);
}

void main(){
    double pi = 0;
    double piPrev = 0;
    int i = 0;
    do{
        piPrev = pi;
        pi= pi + (factorial(i)/(doublefactorial((2 * i + 1))));  //Formel für Kreiszahl 
        printf("%d. %.16f\n", i, 2*pi);
        i++; 
    } while(pi != piPrev);  //Abbruchbedingung ist wenn die summe nicht mehr ansteigt
}

