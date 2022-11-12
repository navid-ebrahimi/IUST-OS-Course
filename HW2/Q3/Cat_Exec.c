#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <threads.h>

void catFunction(char* arg)
{
    char *my_args[3];
    my_args[0] = strdup("cat");
    my_args[1] = strdup(arg);
    my_args[2] = NULL;
    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(my_args[0], my_args);
    }
    else if(pid > 0)
    {
        waitpid(pid, NULL, 0);
    }
    else
    {
        exit(0);
    }
    
}

int main(int argc, char const *argv[]) {
    char *binaryPath = "/bin/cat";
    catFunction(argv[1]);

    return 0;
}