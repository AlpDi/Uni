#include "convex_hull_alp.h"
#include "libBMP.h"
#include <stdio.h>


#define WIDTH 1000
#define HEIGHT 1000

#define xMin -1.00
#define xMax  1.00
#define yMin -1.00
#define yMax  1.00



int main(void){
    int n;
    int i_start = 0;
    int i_switch = 0;
    double x[n];
    double y[n];
    int c;
    int m;
    int M;
    int grid = (int*)malloc(WIDTH * HEIGHT * sizeof(int));

    while (1) {
        printf(" 1) Anzahl der Punkte festlegen\n 2) Punkte von Tastatur einlesen\n 3) Zufallspunkte erzeugen\n 4) Eckpunkte der konvexen Huelle berechnen und ausgeben\n 5) Konvexe Huelle als BMP-Datei ausgeben\n 6) Programm beenden\n");
        int user_input;
        scanf("%d", &user_input);
        if (user_input > 0 && user_input <= 6) {
            if (user_input == 1) {
            printf("Anzahl der Punkte:\n");
            scanf("%d", &n);
            } else if (user_input == 2) {
            read_points(n, x, y);
            } else if (user_input == 3) {
            rand_points(n, x, y);
            } else if (user_input == 4) {
            M = hull(n, x, y, c);
            display_corners(M, x,y,c);
            } else if (user_input == 5) {
            plot_hull(m,n,x,y,c);
            } else if (user_input == 6) {
            return 0;
            } else {return 1;}
        }
    }
}
