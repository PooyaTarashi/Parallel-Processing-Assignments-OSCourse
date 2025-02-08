#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    char target[2048];
    scanf("%s", target);

    char* dirPath;

    int path_length = strlen(target); 
    
    int last_slash_index = strrchr(target, '/');
    dirPath = (char*)malloc(sizeof(char) * (last_slash_index + 1));
    strncpy(dirPath, target, last_slash_index);
    dirPath[last_slash_index] = 0;

    char compile_command[256];
    snprintf(compile_command, sizeof(compile_command), "gcc %s -o %s/a.out", target, dirPath);

    system(compile_command);
    chdir(dirPath);
    int pid = fork();
    if(pid == 0)
        execvp("./a.out",NULL);
    else
    {
        wait(NULL);
        // Do the work that this app wants to do
        printf("Weeeee! I'm a helicopter! (from main app)");
    }
    
}