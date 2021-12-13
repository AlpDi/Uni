#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "libBMP.h"

#include "convex_hull_alp.h"

#define W 1000
#define H 1000

#define X_MIN -1.00
#define X_MAX  1.00
#define Y_MIN -1.00
#define Y_MAX  1.00

int toMath(int bmp_x, int bmp_y, double *x, double *y, int WIDTH,int HEIGHT){
    *x = X_MIN + (bmp_x * (X_MAX - X_MIN)) / WIDTH;
    *y = Y_MIN + ((HEIGHT - bmp_y) * (Y_MAX - Y_MIN) / HEIGHT);
}

int toBMP(double x, double y, int *bmp_x, int *bmp_y, int WIDTH, int HEIGHT){
    *bmp_x=((x-X_MIN)*WIDTH)/(X_MAX-X_MIN);
    *bmp_y=HEIGHT-((y-Y_MIN)*HEIGHT)/(Y_MAX-Y_MIN);
}

void print_points(double x[], double y[], int N){

    for (int i = 0; i < N; i++){
        printf("%d. %lf %lf\n",i, x[i], y[i] );
    }
}

void read_points(int n, double x[], double y[]){
    for(int i = 0; i < n; i++){
        printf("x-Wert: \n");
        scanf("%lf", &x[i]);
        printf("y-Wert: \n");
        scanf("%lf", &y[i]);
    }
}


void rand_points(int n, double x[], double y[]){

    time_t t;

    srand((unsigned) time(&t));

    for(int i = 0; i < n; i++){
        x[i] = 20 * ( (1.0*rand() )/RAND_MAX) - 10;
        y[i] = 20 * ( (1.0*rand() )/RAND_MAX) - 10;
    }
}


void display_corners(int m, double x[], double y[], int c[]){
    for(int i = 0; i < m; i++){
        printf("x: %lf y: %lf\n", x[c[i]], y[c[i]]);
    }
}


void switch_point(int n, double x[], double y[], int* i_start, int* i_switch ){


    int min = y[0];
    int max = y[0];
    //returns index of min(y) and max(x)
    for (int i = 0; i < n; i++) {
        if(y[i] < min){min = y[i]; *i_start = i;}
        if(y[i] > max){max = y[i]; *i_switch = i;}
    }
}



int hull(int n, double x[], double y[], int c[]){
    int i_start = 0;
    int i_switch = 0;
    int m = 1;
    int up = 1;
    int J = 0;
    double Qx = 0;
    double Qy = 0;
    double phi = atan2((x[0]-x[0]),(y[0]-y[0]));;
    double phi_s;
    double length;


    if(n==1){return 1;}
    for(int i = 0; i<n; i++){
        c[i] = i;
    }
    switch_point(n,x,y,&i_start,&i_switch);
    if(i_start != 0){
        c[0] = i_start;
        c[i_start] = 0;
    }
    for(int j = m; j < n; j++){
        if(j == n-1){j=0;}
        Qx = x[c[j]] - x[c[m-1]];
        Qy = y[c[j]] - y[c[m-1]];
        phi = atan2(Qx, Qy);
        if(j==1){phi_s = phi;}
        length = hypot(Qx, Qy);
        if(up == 1&&phi < phi_s){
            phi_s = phi;
            J = j;
        }
        if(up == 0&&phi > phi_s){
            phi_s = phi;
            J = j;
        }
        if(j == 0){
            return m;
        }
        if(m != j){
            int temp = c[m];
            c[m] = c[j];
            c[j] = temp;
        }
        if(c[m] == i_switch){
            up = 0;
            m++;
        }
    }
}


void toBMP(double matX, double matY, int *bmpX, int *bmpY) {
  *bmpX = (matX - MIN_X) * WIDTH / (MAX_X - MIN_X);
  *bmpY = HEIGTH - (matY - MIN_Y) * HEIGTH / (MAX_Y - MIN_Y);
}

void toMAT(int bmpX, int bmpY, double *matX, double *matY) {
  *matX = MIN_X + bmpX * (MAX_X - MIN_X) / WIDTH;
  *matY = MIN_Y + (HEIGTH - bmpY) * (MAX_Y - MIN_Y) / HEIGTH;
}

void plot_hull(int m, int n, double x[], double y[], int c[]){
  double smallest_x = x[0];
  double smallest_y = y[0];
  double biggest_x = x[0];
  double biggest_y = y[0];
  for (int i = 1; i < n; i++) {
    if (smallest_x > x[i]) {smallest_x = x[i]};
    if (smallest_y > y[i]) {smallest_y = y[i]};
    if (biggest_x > x[i]) {biggest_x = x[i]};
    if (biggest_y > y[i]) {biggest_y = y[i]};
  }

  int grid = (int*)malloc(WIDTH* HEIGTH * sizeof(int));
  for (int i = 0; i < WIDTH * HEIGTH; i++) {grid[i] = COLOR_WHITE;}


  for ?


  for (int i = 0; i < n; i++) {
    int bmp_x, bmp_y;
    toBMP(x[i], y[i], bmpX, bmpY);
    grid[bmpX + bmpY * WIDTH] = COLOR_BLACK;
  }


}
