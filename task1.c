#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 80

int main() {
    char line[MAX_LINE_LENGTH];
    pid_t pid;
    int status;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);  /* Ensure prompt is displayed */

        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove trailing newline character */
        line[strcspn(line, "\n")] = '\0';

        /* Create a child process and execute the command */
        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
            /* Child process */
            execlp(line, line, NULL);
            /* If execution reaches here, it means the command was not found */
            fprintf(stderr, "%s: command not found\n", line);
            exit(1);
        } else {
            /* Parent process */
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}

