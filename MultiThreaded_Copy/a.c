#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>

void getArgs(char* srcPH, char* destPH)
{
    char src[256] = "./";
    char dest[256] = "./";
    char getSrc[256] = "hi";
    char getDest[256] = "bye";
    scanf("%s%s", getSrc, getDest);
    strcat(src, getSrc);
    strcat(dest, getDest);
    strcpy(srcPH, src);
    strcpy(destPH, dest);
}

void copyFile(char *sourcePath, char *destPath) {
    FILE *sourceFile = fopen(sourcePath, "rb");
    FILE *destFile = fopen(destPath, "wb");

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, destFile);
    }

    fclose(sourceFile);
    fclose(destFile);
}

int countThreads(char* src)
{
    int tCount = 0;
    DIR *dir1 = opendir(src);
    if (dir1 == NULL) return 0;
    struct dirent* entry1;
    while ((entry1 = readdir(dir1)) != NULL) {
        if (entry1->d_type == DT_DIR && strcmp(entry1->d_name, ".") != 0 && strcmp(entry1->d_name, "..") != 0) {
            tCount++;
        }
    }
    closedir(dir1);
}

void getNewPath(char* newPath, char* formerPath, char* entName)
{
    strcat(newPath, formerPath);
    strcat(newPath, "/");
    strcat(newPath, entName);
}

void *cpt(void *args) {
    char **arg_ptr = (char **)args;
    char *src = arg_ptr[0];
    char *dest = arg_ptr[1];

    int tCount = countThreads(src);
    pthread_t* threadsList = (pthread_t*)malloc(tCount * sizeof(pthread_t));

    DIR *dir = opendir(src);
    if (dir == NULL) pthread_exit(NULL);
    struct dirent* entry;
    int usedThreads = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            char newSrc[256] = "";
            getNewPath(newSrc, src, entry->d_name);

            char newDest[256] = "";
            getNewPath(newDest, dest, entry->d_name);

            if (entry->d_type == DT_DIR) {
                mkdir(newDest, 0755);
                pthread_t t;
                char** args = (char**)malloc(2 * sizeof(char*));
                args[0] = (char*)malloc(strlen(newSrc) + 1);
                strcpy(args[0], newSrc);
                args[1] = (char*)malloc(strlen(newDest) + 1);
                strcpy(args[1], newDest);
                pthread_create(&t, NULL, cpt, args);
                threadsList[usedThreads++] = t;
            } else { 
                copyFile(newSrc, newDest);
            }
        }
    }

    for (size_t i = 0; i < usedThreads; i++)
        pthread_join(threadsList[i], NULL);

    free(threadsList);
    closedir(dir);
    return NULL;
}

int main() {
    char src[256];
    char dest[256];
    getArgs(src, dest);

    pthread_t mainThread;
    char** args = (char**)malloc(2 * sizeof(char*));
    args[0] = (char*)malloc(strlen(src) + 1);
    strcpy(args[0], src);
    args[1] = (char*)malloc(strlen(dest) + 1);
    strcpy(args[1], dest);

    pthread_create(&mainThread, NULL, cpt, args);
    pthread_join(mainThread, NULL);

    free(args[0]);
    free(args[1]);
    free(args);

    return 0;
}

