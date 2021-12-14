#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "libBMP.h"
#include "convex_hull_alp.h"

#define W 1000
#define H 1000

#define xMin -1.00
#define xMax  1.00
#define yMin -1.00
#define yMax  1.00

int toMath(int bmp_x, int bmp_y, double *x, double *y, int WIDTH,int HEIGHT){
    *x = xMin + (bmp_x * (xMax - xMin)) / WIDTH;
    *y = yMin + ((HEIGHT - bmp_y) * (yMax - yMin) / HEIGHT);
}

int toBMP(double x, double y, int *bmp_x, int *bmp_y, int WIDTH, int HEIGHT){
    *bmp_x=((x-xMin)*WIDTH)/(xMax-xMin);
    *bmp_y=HEIGHT-((y-yMin)*HEIGHT)/(yMax-yMin);
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
    int j;
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
    for(int j_ = m; j_ <= n; j_++){
        //cyclic loop
        j = j_%n;
        Qx = x[c[j]] - x[c[m-1]];
        Qy = y[c[j]] - y[c[m-1]];
        //angle between Qj and x-axis
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
        if((x[c[J]] == x[c[0]]) && y[c[J]] == x[c[0]]){
            return m;
        }
        if(m != j){
            int temp = c[m];
            c[m] = c[j];
            c[j] = temp;
        }
        if(c[m] == i_switch){
            up = 0;
        }
        m++;
    }
}

void plot_hull(int m, int n, double x[], double y[], int c[]){
  double smallest_x = x[0];
  double smallest_y = y[0];
  double biggest_x = x[0];
  double biggest_y = y[0];
  for (int i = 1; i < n; i++) {
    if (smallest_x > x[i]) {smallest_x = x[i];}
    if (smallest_y > y[i]) {smallest_y = y[i];}
    if (biggest_x > x[i]) {biggest_x = x[i];}
    if (biggest_y > y[i]) {biggest_y = y[i];}
  }

  int *grid = (int*)malloc(W* H * sizeof(int));
  for (int i = 0; i < W * H; i++) {grid[i] = COLOR_WHITE;}

  int last_point = m;
  for (int i = 0; i < m; i++) {
    double a = y[c[i]] - y[c[last_point]];
    double b = y[c[last_point]] - y[c[i]];
    double d = a * x[c[last_point]] + b * y[c[last_point]];
    last_point = i;
    for (int j = 0; j < W * H; j++) {
      if (a * (j % W) + b * (j / W) == d) {
        grid[j] = COLOR_RED;
      }
    }
  }  


  for (int i = 0; i < n; i++) {
    int bmp_x, bmp_y;
    toBMP(x[i], y[i], bmp_x, bmp_y, W, H);
    grid[bmp_x + bmp_y * W] = COLOR_BLACK;
  }
  bmp_create("hull.bmp", grid, W, H);
    free(grid);

}