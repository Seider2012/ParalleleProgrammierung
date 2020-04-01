
#include "EX1Cri.c"
#include "EX1Atm.c"
#include "EX1Red.c"


int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Arguments are missing!\n");
        return EXIT_FAILURE;
    }
    char *p;
    int choice = strtol(argv[1], &p, 10);
    int ex;
    if (choice == 1) {
        ex = ex + EX1Cri();
        ex = ex + EX1Atm();
        ex = ex + EX1Red();
        return ex;
    } else {

        return ex;

    }
}
