#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void cd(int argNo, char *arg[]) {
    char *dir = arg[1];
    int fuck;
    
    if (argNo > 2)
        printf("cd: wrong number of arguments\n");
    else if (argNo == 1 || strcmp(arg[1], "~")==0)
        chdir(getenv("HOME"));
    else if (chdir(dir) == -1)
        printf("%s:cannot change directory\n", dir);
    
};

void quit(int argNo) {
    if (argNo > 1)
        printf("exit: wrong number of arguments\n");
    else
        exit(0);
};

int main(int argc, char *argv[]) {
    int argNo;
    char buf[256];
    char *token, *arg[256];
    pid_t child_pid;

    while (true) {

        char cwd[PATH_MAX + 1];
        argNo = 0;
        setenv("PATH", "/bin:/usr/bin:.", 1);


        if (getcwd(cwd, PATH_MAX + 1) != NULL) {
            printf("[3150 shell: %s", cwd);
            printf("]$");
            fgets(buf, 255, stdin);
        }

        token = strtok(buf, " \n\t");

        if (token == NULL)
            continue;

        while (token != NULL) {
            arg[argNo++] = token;
            token = strtok(NULL, " \n\t");
        }

        arg[argNo] = NULL;

        if (strcmp(*arg, "cd") == 0) {
            cd(argNo, arg);
        } else if (strcmp(*arg, "exit") == 0) {
            quit(argNo);
        } else {

            if (!(child_pid = fork())) {

                execvp(*arg, arg);
                
                if (errno == ENOENT) 
                    printf("%s:Command not found\n", *arg);
                else
                    printf("%s: unknown error\n",*arg);
                
                _exit(1);
            }else
                waitpid(child_pid, NULL, WUNTRACED);
        }

    }
    return 0;
}
