#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t line_length;

    while (1)
    {
        printf("$ "); /* Display the prompt */
        line_length = getline(&buffer, &bufsize, stdin); /* Read input from the user */
        buffer[line_length - 1] = '\0'; /* Replace newline with null terminator */

        if (line_length == -1) /* Check for EOF condition */
        {
            if (isatty(STDIN_FILENO))
                printf("\n"); /* Print newline for clarity */
            break;
        }

        /* Tokenize the input line to extract command and arguments */
        char *token;
        char *args[10]; /* Assuming maximum 10 arguments */
        int arg_count = 0;

        token = strtok(buffer, " "); /* Get the first token (command) */
        while (token != NULL)
        {
            args[arg_count++] = token; /* Store token in args array */
            token = strtok(NULL, " "); /* Get next token */
        }
        args[arg_count] = NULL; /* Set last element to NULL to indicate end of arguments */

        /* Execute the command with its arguments */
        if (execve(args[0], args, NULL) == -1)
        {
            perror("Error"); /* Print error message if execve fails */
            if (isatty(STDIN_FILENO))
                printf("$ "); /* Display the prompt again */
        }
    }

    free(buffer); /* Free dynamically allocated memory */
    return (0);
}

