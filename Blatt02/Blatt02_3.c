#include <stdio.h>
#include <stdlib.h>

void create_raute();
void print_rows();


void main(){

    int n = 10;     //scanf possible
create_raute(n);
}


void print_rows(int n, int i){
    printf("%*s", (n - i) * 2, "");         //creates dynamic indent  
    for(int j = 1; j <= i; j++){            //loop for first part of rows
        printf("%d ", j);
    }

    for(int k = i -1; k > 0; k--){          //loop for second part of rows
        printf("%d ", k);
    }
    printf("\n");
}



void create_raute(int n){
    for(int i = 0; i <= n; i++){                //loop to count up to n
        print_rows(n, i);
    }

    for(int i = n-1; i > 0; i--){               //count down from n-1
        print_rows(n, i);
    }
}