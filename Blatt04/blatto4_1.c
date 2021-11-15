#include <stdlib.h>
#include <math.h>
#include <stdio.h>


float u(float k, float r){
    return k/(1+k*(1-k)*r);
}

float k(float u, float r){
    //return  (sqrt(pow(r,2)*pow(u,2)+2*r*(2*u-1)*u+1)+r*u-1)/2*r*u;
    if(u*r==0){
        return u;
    }
    else{
    return (-(1-u*r)+sqrt(pow((1-u*r),2)+4*r*pow(u,2)))/2*u*r ; 
    }
}

void table(){
    printf(" k     | r     | f(k,r)  | g(f(k,r),r)\n");
    printf("-------------------------------------\n");

    for(float r = 0; r <= 5; r = r + 1){
        for(float i = 0; i <= 1.1; i=i+0.1){ //i is k
            printf(" %.1f   | %.1f   | %.1f     | %.1f       \n", i,r,u(i,r),k(u(i,r),r));
        }
    }


    printf("\n\n\n");


    printf(" u     | r     | g(u,r)  | f(g(u,r),r)\n");
    printf("-------------------------------------\n");

    for(float r = 0; r <= 5; r = r + 1){
        for(float i = 0; i <= 5; i=i+1){ //i is u
            printf(" %.1f   | %.1f   | %.1f     | %.1f       \n", i,r,k(i,r),u(k(i,r),r));
        }
    }
}

void plot(double r){
    for(double i=3.0; i>0; i = i - 0.1){        //placement of y-axis
        printf("|");
        for(double j=k(i,r); j>0; j = j-0.1){   //placement of k value
            printf("   ");
        } 
        printf("x\n");
    }
    printf("------------------------------------------------------------------------------------------------"); // x-axis
}



int main(){
    table(0,0,0);
    printf("\n\n");
    plot(0.0); //r=0.0 da funktion für k falsch ist und nur der wert funktioniert da k=u bei r = 0
    return 0;
}