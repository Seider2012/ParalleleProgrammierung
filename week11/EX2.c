
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

void S2(int a[], int b[], int c[], int d[], int e[], int f[], int N) {
    for (int i = 1; i < N - 2; ++i) {
        b[i] = a[i - 1] + 1;
        c[i] = 2 * a[i];
        d[i] = a[i + 1] + 2;
        e[i + 1] = a[i + 2] + 3;
        f[i + 1] = e[i] + 4;
    }
};

double hypot(double c1, double c2) {
    return (sqrt((c1 * c1 + c2 * c2)));
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


void f5(int a[], int b[], int c[], int N) {
    for (int i = 0; i < N; ++i) {
        if (N % 2) {
            a[i] = b[i] + 5;
        } else {
            a[i] = c[i] + 5;
        }
    }
};

void S5(int a[], int b[], int c[], int N) {
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

void f6(int a[], int b[], int c[], int N) {
    int sum_a, sum_b, sum_c;
    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
        sum_b += b[i];
        sum_c += c[i];
    }
};
void S6(int a[], int b[], int c[], int N) {
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

void f7(int a[], int N) {
    int sum = 0;
    int min = a[0];
    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
    }
    for (int i = 0; i < N; ++i) {
        sum += a[i];
    }
};
void S7(int a[], int N) {
    int sum = a[0];
    int min = a[0];
    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
        sum += a[i];
    }
};

void f8(int a[], int b[],int c[], int N) {

    for (int i = 0; i < N; ++i) {
        if (i % 2) {
            a[i] = b[i] + 4;
        } else {
            a[i] = c[i] + 5;
        }
    }

};

void S8(int a[], int b[],int c[], int N) {
    for (int i = 1; i < N; i+=2) {
        a[i] = b[i] + 4;
    }
    for (int i = 0; i < N; i+=2) {
        a[i] = c[i] + 5;
    }
};
void f9(int *t1[], int *t2[], int *t3[], int N) {

    int (*a)[N] = (int (*)[N]) t1;
    int (*b)[N] = (int (*)[N]) t2;
    int (*c)[N] = (int (*)[N]) t3;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                c[i][j] = a[i][k] * b[k][j];
            }
        }
    }
};
void S9(int *t1[], int *t2[], int *t3[], int N) {

    int (*a)[N] = (int (*)[N]) t1;
    int (*b)[N] = (int (*)[N]) t2;
    int (*c)[N] = (int (*)[N]) t3;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                c[i][j] = a[i][k] * b[k][j];
            }
        }
    }
};
int main(int argc, void **argv) {
    int n = 10;
    if (argc == 2) {
        char **p;
        n = (int) strtol(argv[1], p, 10);
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


    int t1[n][n];
    int t2[n][n];
    int t3[n][n];

    f1(a, b, n);
    f2(a, b, c, d, e, f, n);
    f3(a, n);
    f5(a, b, c, n);
    f6(a, b, c, n);
    f7(a, n);
    f8(a,b,c,n);
    f9(t1, t2, t3, n);
    S1(a, b, n);
    S2(a, b, c, d, e, f, n);
    S3(a, n);
    S5(a, b, c, n);
    S6(a, b, c, n);
    S7(a, n);
    S8(a,b,c,n);
    S9(t1, t2, t3, n);


    for (int i = 0; i < n; i++) {
        printf("a = %d\n", a[i]);
        printf("b = %d\n", b[i]);
        printf("c = %d\n", c[i]);
        printf("d = %d\n", d[i]);
        printf("e = %d\n", e[i]);
        printf("f = %d\n", f[i]);
        for (int j = 0; j < n; j++) {
            printf("t1 = %d ", t1[i][j]);
        }
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("t2 = %d ", t1[i][j]);
        }
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("t3 = %d ", t1[i][j]);
        }
        printf("\n");

    }


}