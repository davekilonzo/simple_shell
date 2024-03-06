#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
    char buffer[BUFFER_SIZE];
    
    while (1)
    {
        printf("$ "); /* Display the prompt */
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) /* Read input from the user */
        {
            printf("\n"); /* Print a new line before exiting */
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; /* Remove the trailing newline character, if present */

        if (execve(buffer, (char *[]) {buffer, NULL}, NULL) == -1) /* Execute the command */
        {
            perror("execve"); /* Print error message */
        }
    }

    return (0);
}

