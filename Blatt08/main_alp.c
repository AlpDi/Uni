#include "convex_hull_alp.h"
#include "libBMP.h"
#include <stdio.h>

int main(void){
    double x[3];
    double y[3];
    rand_points(2,x,y);
    printf("%lf %lf",x[1], x[0]);
}