#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

struct dirent **thrDir;

int calculateSeqSize(const char *arg) {
    struct dirent *pDirent;
    struct stat buffer;
    DIR *pDir;
    size_t folder_size = 0;
    pDir = opendir(arg);
    if (pDir == NULL) {
        fprintf(stderr, "Cannot open directory '%s'\n", arg);
        return -1;
    }

    int cur_size;
    while ((pDirent = readdir(pDir)) != NULL) {
        if (pDirent->d_name[0] == '.' && (pDirent->d_name[1] == '.' || pDirent->d_name[1] == '\0'))
            continue;

        char *fullpath = malloc(strlen(arg) + strlen(pDirent->d_name) + 2);


        if (fullpath == NULL) { return -1; }
        sprintf(fullpath, "%s\\%s", arg, pDirent->d_name);
        int stat = lstat(fullpath, &buffer);
        cur_size = buffer.st_size;
        if (stat == -1) {
            fprintf(stderr, "Error opening file: %s\n", strerror(errno));
        } else if (cur_size == 0) {
            cur_size = calculateSeqSize(fullpath);
        }

        folder_size += cur_size;
        printf("[%s] size=%d\n", pDirent->d_name, cur_size);

        free(fullpath);
    }
    // close dir
    closedir(pDir);
    return folder_size;
}

int measureMethod(const char *arg, struct dirent *pDirent) {

    int cur_size;
    struct stat buffer;
    char *fullpath = malloc(strlen(arg) + strlen(pDirent->d_name) + 2);
    if (fullpath == NULL) { fprintf(stderr, "Error creating path: %s\n", strerror(errno)); }
    sprintf(fullpath, "%s\\%s", arg, pDirent->d_name);

    if (pDirent->d_type == DT_DIR) {
        cur_size = calculateParSize(fullpath);
    }else{
    int stat = lstat(fullpath, &buffer);
    cur_size = buffer.st_size;
    if (stat == -1) {
        fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    }


   // printf("[%s] size=%d\n", pDirent->d_name, cur_size);
    }

    free(fullpath);
return cur_size;

}


int calculateParSize(const char *arg) {
    DIR *pDir;
    size_t folder_size = 0;
    pDir = opendir(arg);
    if (pDir == NULL) {
        fprintf(stderr, "Cannot open directory '%s'\n", arg);
        return -1;
    }
#pragma omp parallel reduction(+:folder_size)
#pragma omp master
    {
        struct dirent *dirents[2];
        do {
            dirents[0] = readdir(pDir);
            if (dirents[0] != NULL) {
                while ((dirents[0]->d_name[0] == '.' &&
                        (dirents[0]->d_name[1] == '.' ||
                         dirents[0]->d_name[1] == '\0'))) {
                    dirents[0] = readdir(pDir);
                    if (dirents[0] == NULL)
                        break;
                }
            }
            if (dirents[0] != NULL) {
                struct dirent *temp = (struct dirent *) malloc(sizeof(struct dirent));
                memcpy(temp, dirents[0], sizeof(struct dirent));
                dirents[0] = temp;
            }
            dirents[1] = readdir(pDir);
#pragma omp task shared(arg, dirents, folder_size)
            {
                if (dirents[0] != NULL) {
                    folder_size+= measureMethod(arg, dirents[0]);
                } else {
                    free(dirents[0]);
                }
            }
#pragma omp task shared(arg, dirents, folder_size)
            {
                if (dirents[1] != NULL) {
                    folder_size+= measureMethod(arg, dirents[1]);
                }
            }

#pragma omp taskwait
        }while (dirents[1] != NULL);
    }
// close dir
    closedir(pDir);
    return folder_size;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: .%s <dirname>\n", argv[0]);
        return EXIT_FAILURE;
    }
    double start_time;
    double end_time;
    unsigned long long size;

/*
    start_time = omp_get_wtime();
    size = calculateSeqSize(argv[1]);
    end_time = omp_get_wtime();

    if (size == -1) {
        fprintf(stderr, "Error appeared: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }


    printf("Sequenziel size=%d Bytes time: %2.4f seconds\n", size,
           end_time - start_time);
*/

    start_time = omp_get_wtime();
    size = calculateParSize(argv[1]);
    end_time = omp_get_wtime();
    if (size == -1) {
        fprintf(stderr, "Error appeared: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }


    printf("Parallel size=%u Bytes time: %2.4f seconds\n", size,
           end_time - start_time);
    return EXIT_SUCCESS;
}
