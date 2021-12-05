int springer( int zeile, int spalte, int num );
#include <stdio.h>

#define N 5
#define MAX N*N-1

//int n = 8;
int board[N][N] = { 0 }; //erreichte Felder
//int moves[8][2] = { {-2,-1}, {-1,-2}, {-2,1}, {-1,2}, {2,-1}, {1,-2}, {2,1}, {1,2}}; //moegliche Schritte #1
//int moves[8][2] = { {-2,1}, {-2,-1}, {-1,2}, {-1,-2}, {2,1}, {2,-1}, {1,2}, {1,-2}}; //moegliche Schritte #2
//int moves[8][2] = { {-1,2}, {-1,-2}, {-2,1}, {-2,-1}, {2,1}, {2,-1}, {1,2}, {1,-2}}; //moegliche Schritte #3
int moves[8][2] = {{2,1}, {2,-1}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1}, {1,2}, {1,-2}}; //moegliche Schritte #4
//int it = 0;

int main(int argc, const char * argv[]) {

    //Rekursion starten
    springer(0, 0, 1);
    printf("%d ok: %d,%d\n", 0,0,0);
    //Endzeit
    

    return 0;
    
}

int springer( int zeile, int spalte, int num ){
    //++it;
    int nzeile, nspalte, i;
    
    //Platz belegen
    board[zeile][spalte] = num;
    
    //Alle N Moeglichen Zuege durchprobieren
    for(i = 0; i < 8; i++){
        //++it;
        
        //Neue Position
        nzeile = zeile + moves[i][0];
        nspalte = spalte + moves[i][1];
        
        //Ist Zug ist im Spielfeld
        if(nzeile >= 0 && nzeile < N && nspalte >= 0 && nspalte < N){
        
            //Platz ist frei?
            if(!board[nzeile][nspalte]){

                //Ende oder Rekursion
                if(num == MAX || springer(nzeile, nspalte, num+1)){
                    printf("%d ok: %d,%d\n", num, nzeile,nspalte);
                    return 1;
                }
            }
        }
    }
    
    // Freigeben, falls Nachfolgende Schritte nicht moeglich
    board[zeile][spalte] = 0;
    return 0;
}