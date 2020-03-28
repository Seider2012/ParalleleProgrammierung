#include "week3/EX2.c"
#include <stdlib.h>


    int main(int argc, char *argv[]) {

        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                EX2(j, i * 10000);
            }
        }

        return EXIT_SUCCESS;

}
