#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "simple_shell.h"

#define MAX_LINE_LENGTH 80

void run_shell() {
    char line[MAX_LINE_LENGTH];
    int status;

    while (1) {
        printf("shell> ");
        fflush(stdout);  // Ensure prompt is displayed

        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Check if the line contains more than one word
        if (strchr(line, ' ') != NULL) {
            printf("Error: Command must be a single word\n");
            continue;
        }

        // Remove trailing newline character
        line[strcspn(line, "\n")] = '\0';

        // Create a child process and execute the command
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0) {
            // Child process
            execlp(line, line, NULL);
            // If execution reaches here, it means the command was not found
            printf("Error: Command '%s' not found\n", line);
            exit(1);
        }
        else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }
}

