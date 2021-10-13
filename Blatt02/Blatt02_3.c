#include <stdio.h>
#include <stdlib.h>

void create_raute();


void main(){

    int n = 4;
    
create_raute(n);

/*
    for(int i = 0; i <= n; i++){                //loop to count up to n
        printf("%*s", (n - i) * 2, "");         //creates dynamic indent  
        for(int j = 1; j <= i; j++){            //loop for first part of rows
            printf("%d ", j);
        }
        for(int k = i -1; k > 0; k--){          //loop for second part of rows
            printf("%d ", k);
        }
        printf("\n");
    }

    for(int i = n-1; i > 0; i--){               //count down from n-1
        printf("%*s", (n - i) * 2, "");         
        for(int j = 1; j <= i; j++ ){           //same as loop above
            printf("%d ", j);
        }
        for(int k = i-1; k > 0; k--){
            printf("%d ", k);
        }
        printf("\n");
    }
*/
}

void create_raute(int n){
        for(int i = 0; i <= n; i++){                //loop to count up to n
        printf("%*s", (n - i) * 2, "");         //creates dynamic indent  
        for(int j = 1; j <= i; j++){            //loop for first part of rows
            printf("%d ", j);
        }
        for(int k = i -1; k > 0; k--){          //loop for second part of rows
            printf("%d ", k);
        }
        printf("\n");
    }

        for(int i = n-1; i > 0; i--){               //count down from n-1
        printf("%*s", (n - i) * 2, "");         
        for(int j = 1; j <= i; j++ ){           //same as loop above
            printf("%d ", j);
        }
        for(int k = i-1; k > 0; k--){
            printf("%d ", k);
        }
        printf("\n");
    }
}