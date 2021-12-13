void read_points(int n, double x[], double y[]);
void rand_points(int n, double x[], double y[]);
void display_corners(int m, double x[], double y[], int c[]);
void switch_point(int n, double x[], double y[], int* i_start, int* i_switch );
int hull(int n, double x[], double y[], int c[]);
void plot_hull(int m, int n, double x[], double y[], int c[]);
void print_points(double x[], double y[], int N);

int toMath(int bmp_x, int bmp_y, double *x, double *y, int WIDTH, int HEIGHT);

int toBMP(double x, double y, int *bmp_x, int *bmp_y, int WIDTH, int HEIGHT);