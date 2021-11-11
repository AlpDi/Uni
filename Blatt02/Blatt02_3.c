#include <stdio.h>
#include <stdlib.h>

void createSchmetterling();
void printRows();


int main(){

    int n = 9;     //nur bis 9 weil double digits zu breit sind 
    
    createSchmetterling(n);
}


void printRows(int n, int i){
    for(int j = 1; j <= i; j++){            //loop for first part of rows
            printf("%d ", j); 
    }
    printf("%*s", (n - i) * 2, "");      
    if(i!=n){                               //no dynamic indent for i==n since only one n gets printed
        printf("%*s",2- (n - i) * 2, "");
    }

    for(int k = i; k > 0; k--){          //loop for second part of rows
        if(k!=n){
            printf("%d ", k);
        } 
    } 
    printf("\n");
}



void createSchmetterling(int n){
    for(int i = 0; i <= n; i++){                //loop to count up to n
        printRows(n, i);
    }

    for(int i = n-1; i > 0; i--){               //count down from n-1
        printRows(n, i);
    }
}