#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int calculateSize(const char *arg){
    struct dirent *pDirent;
    struct stat buffer;
    DIR *pDir;
    size_t folder_size=0;
    pDir = opendir (arg);
    if (pDir == NULL) {
        fprintf (stderr,"Cannot open directory '%s'\n", arg);
        return -1;
    }

    int cur_size;
    while ((pDirent = readdir(pDir)) != NULL) {

        if(pDirent->d_name[0]=='.')
            continue;

        char *fullpath = malloc(strlen(arg) + strlen(pDirent->d_name) + 2);
        if (fullpath == NULL) { return -1; }
        sprintf(fullpath, "%s\\%s", arg, pDirent->d_name);
        int stat=lstat(fullpath,&buffer);
        cur_size=buffer.st_size;
        if(stat==-1){
            fprintf(stderr, "Error opening file: %s\n", strerror( errno ));
        }else if(cur_size==0){
            cur_size=calculateSize(fullpath);
        }

        folder_size+=cur_size;
        printf("[%s] size=%d\n", pDirent->d_name,cur_size);

        free(fullpath);
    }
    // close dir
    closedir (pDir);
    return folder_size;
}


int main (int argc, char *argv[]) {
    if (argc != 2) {
        fprintf (stderr,"Usage: .%s <dirname>\n",argv[0]);
        return EXIT_FAILURE;
    }
    double start_time;
    double end_time;
    int size;
    start_time = omp_get_wtime();
    size=calculateSize(argv[1]);
    end_time = omp_get_wtime();

    if(size==-1){
        fprintf(stderr, "Error appeared: %s\n", strerror( errno ));
        return EXIT_FAILURE;
    }

    printf("size=%d Bytes time: %2.4f seconds\n",size,
           end_time - start_time);
    return EXIT_SUCCESS;
}
