#include <stdio.h>
#include "week3/EX2.c"
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "week3/EX2Dynamic.c"
#include "week3/EX2Static.c"
#include "week3/EX2Guided.c"

    int main(int argc, char *argv[]) {

        for (int i = 1; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                EX2(j, i * 10000);
            }
        }

        return EXIT_SUCCESS;

/*
        char *p;
       errno = 0;
          long var = 0;
       int n;
      int choice;



    if (argc == 4) {
        var = strtol(argv[1], &p, 10);
        n = strtol(argv[2], &p, 10);
        choice = strtol(argv[3], &p, 10);
        printf("%d\n", var);
    }
    if (errno != 0 || *p != '\0' || var > INT_MAX) {
        printf("Der Parameter hat keinen zulässigen Wert.\n");
        return EXIT_FAILURE;
    } else {
        if (choice == 0)
            return EX2Static(var, n);
        else if (choice == 1)
            return EX2Dynamic(var, n);
        else if (choice == 2)
            return EX2Guided(var, n);

    }
    */
    return EXIT_FAILURE;
}
