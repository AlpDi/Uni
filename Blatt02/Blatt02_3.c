#include <stdio.h>
#include <stdlib.h>

void main(){

    int n = 4;
    

    for(int i = 0; i <= n; i++){
        printf("%*s", (n - i) * 2, "");
        for(int j = 1; j <= i; j++){
            printf("%d ", j);
        }
        for(int k = i -1; k > 0; k--){
            printf("%d ", k);
        }
        printf("\n");
    }

    for(int i = n-1; i > 0; i--){
        printf("%*s", (n - i) * 2, "");
        for(int j = 1; j <= i; j++ ){
            printf("%d ", j);
        }
        for(int k = i-1; k > 0; k--){
            printf("%d ", k);
        }
        printf("\n");
    }
}