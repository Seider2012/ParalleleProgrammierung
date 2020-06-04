
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, void **argv) {
    int c2 = 72;
    if (argc == 2) {
        char **p;
        c2 = (int) strtol(argv[1], p, 10);
    }
    printf("%d \n",c2);
    printf("%d=%d \n",c2*32,c2<<5);


    typedef union
    {
        float f;
        struct
        {
            unsigned int mantissa : 23;
            unsigned int exponent : 8;
            unsigned int sign : 1;
        } field;
    } myfloat;

    float t1=123.03;
    printf("%f\n",t1);
    printf("%d \n",((myfloat*)&t1)->field.sign);
    ((myfloat*)&t1)->field.sign^=1;
    printf("%f\n",t1);

    printf("%d=%d \n",c2/8,c2>>3);

}