
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BLOCK_SIZE 64 / sizeof(double)

void f1(int a[], int b[], int N) {
    for (int i = 0; i < N - 1; ++i) {
        a[i] = b[i] + b[i + 1];
    }
};

void S1(int a[], int b[], int N) {
    for (int i = 0; i < N - 1; i += 2) {
        a[i] = b[i] + b[i + 1];
        a[i + 1] = b[i + 1] + b[i + 2];
    }
};

void f2(int a[], int b[], int c[], int d[], int e[], int f[], int N) {
    for (int i = 1; i < N - 2; ++i) {
        b[i] = a[i - 1] + 1;
        c[i] = 2 * a[i];
        d[i] = a[i + 1] + 2;
        e[i + 1] = a[i + 2] + 3;
        f[i + 1] = e[i] + 4;
    }
};

void S2(int N) {
    int a[N];
    int dummy[27];
    int b[N];
    int dummy2[27];
    int c[N];
    int dummy3[27];
    int d[N];
    int dummy4[27];
    int e[N];
    int dummy5[27];
    int f[N];
    for (int i = 1; i < N - 2; ++i) {
        b[i] = a[i - 1] + 1;
        c[i] = 2 * a[i];
        d[i] = a[i + 1] + 2;
        e[i + 1] = a[i + 2] + 3;
        f[i + 1] = e[i] + 4;
    }
};

double hypot(double c1, double c2) {
    return 0.5;//(sqrt((c1 * c1 + c2 * c2)));
};

void f3(int a[], int N) {
    for (int i = 0; i < N; ++i) {
        a[i] *= hypot(0.3, 0.4);
    }
};

void S3(int a[], int N) {
    double factor = hypot(0.3, 0.4);
    for (int i = 0; i < N; ++i) {
        a[i] *= factor;
    }
};


void f4(int *a, int *b, int *c, int N) {
    for (int i = 0; i < N; ++i) {
        if (N % 2) {
            a[i] = b[i] + 5;
        } else {
            a[i] = c[i] + 5;
        }
    }
};

void S4(int *a, int *b, int *c, int N) {
    if (N % 2) {
        for (int i = 0; i < N; ++i) {
            a[i] = b[i] + 5;
        }
    } else {
        for (int i = 0; i < N; ++i) {
            a[i] = c[i] + 5;
        }
    }
};

void f5(int *a, int *b, int *c, int N) {
    int sum_a, sum_b, sum_c;
    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
        sum_b += b[i];
        sum_c += c[i];
    }
};

void S5(int *a, int *b, int *c, int N) {
    int sum_a, sum_b, sum_c;
    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
    }
    for (int i = 0; i < N; ++i) {
        sum_b += b[i];
    }
    for (int i = 0; i < N; ++i) {
        sum_c += c[i];
    }
};

void f6(int *a, int N) {
    int sum = 0;
    int min = a[0];
    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
    }
    for (int i = 0; i < N; ++i) {
        sum += a[i];
    }
};

void S6(int a[], int N) {
    int sum = a[0];
    int min = a[0];
    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
        sum += a[i];
    }
};

void f7(int a[], int b[], int c[], int N) {

    for (int i = 0; i < N; ++i) {
        if (i % 2) {
            a[i] = b[i] + 4;
        } else {
            a[i] = c[i] + 5;
        }
    }
};

void S7(int a[], int b[], int c[], int N) {
    for (int i = 1; i < N; i += 2) {
        a[i] = b[i] + 4;
    }
    for (int i = 0; i < N; i += 2) {
        a[i] = c[i] + 5;
    }
};

void f8(double **t1, double **t2, double **t3, int N) {
    double (*a)[N] = (double (*)[N]) t1;
    double (*b)[N] = (double (*)[N]) t2;
    double (*c)[N] = (double (*)[N]) t3;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                c[i][j] = a[i][k] * b[k][j];
            }
        }
    }
};

void S8(double **t1, double **t2, double **t3, int N) {

    double (*a)[N] = (double (*)[N]) t1;
    double (*b)[N] = (double (*)[N]) t2;
    double (*c)[N] = (double (*)[N]) t3;

    for (int ic = 0; ic < N; ic += BLOCK_SIZE) {
        for (int jc = 0; jc < N; jc += BLOCK_SIZE) {
            for (int i = ic; i < (N > ic + BLOCK_SIZE - 1 ? ic + BLOCK_SIZE - 1 : N); ++i) {
                for (int j = jc; j < (N > jc + BLOCK_SIZE - 1 ? jc + BLOCK_SIZE - 1 : N); ++j) {
                    for (int k = 0; k < N; ++k) {
                        c[i][j] = a[i][k] * b[k][j];
                    }
                }
            }
        }
    }
}

int main(int argc, void **argv) {
    int n = 100;
    int p = 0;
    int o = 0;
    if (argc == 3) {
        char **b;
        o = (int) strtol(argv[1], b, 10);
        p = (int) strtol(argv[2], b, 10);
    }
    if (n % 2) {

    } else {
        n++;
    }

    int a[n];
    int b[n];
    int c[n];
    int d[n];
    int e[n];
    int f[n];


    double t1[n][n];
    double t2[n][n];
    double t3[n][n];
    switch (o) {
        case 1:
            f1(a, b, n);
            break;
        case 2:
            f2(a, b, c, d, e, f, n);
            break;
        case 3:
            f3(a, n);
            break;
        case 4:
            f4(a, b, c, n);
            break;
        case 5:
            f5(a, b, c, n);
            break;
        case 6:
            f6(a, n);
            break;
        case 7:
            f7(a, b, c, n);
            break;
        case 8:
            f8(t1, t2, t3, n);
            break;
        case 9:
            S1(a, b, n);
            break;
        case 10:
            S2( n);
            break;
        case 11:
            S3(a, n);
            break;
        case 12:
            S4(a, b, c, n);
            break;
        case 13:
            S5(a, b, c, n);
            break;
        case 14:
            S6(a, n);
            break;
        case 15:
            S7(a, b, c, n);
            break;
        case 16:
            S8(t1, t2, t3, n);
            break;
    }


    if (p) {
        for (int i = 0; i < n; i++) {
            printf("a = %d\n", a[i]);
            printf("b = %d\n", b[i]);
            printf("c = %d\n", c[i]);
            printf("d = %d\n", d[i]);
            printf("e = %d\n", e[i]);
            printf("f = %d\n", f[i]);
            for (int j = 0; j < n; j++) {
                printf("t1 = %f ", t1[i][j]);
            }
            printf("\n");
            for (int j = 0; j < n; j++) {
                printf("t2 = %f ", t1[i][j]);
            }
            printf("\n");
            for (int j = 0; j < n; j++) {
                printf("t3 = %f ", t1[i][j]);
            }
            printf("\n");
        }
    }


    return EXIT_SUCCESS;
}