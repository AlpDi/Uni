#include <math.h>
#include <stdio.h>

int main()
{
    double e;
    int i = 1;

    do
    {
        e = 1.0 / pow(2, i);
        
        printf("%d\t%.100f\n", i++, e);
    } while (1 + (e / 2) > 1);  //2 + e >= 2 ,e->0 , 2>= 2 hat keine abbruchbedingung 

    printf("1 + ((1 / 2 ^ %d ) / 2) == 1\n", i);
    return 0;
}


