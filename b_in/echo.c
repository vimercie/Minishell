#include "../inc/minishell.h"

int echo_n(char *input, int n)
{
    char *line;
    size_t len;
    int exit_status = 0;
    
    // Allocate memory for input
    line = malloc(strlen(input) + 1);
    if (line == NULL) {
        strerror(errno);
        return -1;
    }
    strcpy(line, input);
    
    // Clear the readline history
    rl_clear_history();
    
    // Place the input on a new line
    rl_on_new_line();
    
    // Replace the readline line with the input
    rl_replace_line(line, 0);
    
    // Redisplay the line
    rl_redisplay();
    
    // Print the input and add it to the readline history
    if (n == 1) {
        printf("%s", line);
    } else {
        printf("%s\n", line);
    }
    add_history(line);
    
    // Free the allocated memory
    free(line);
    
    return exit_status;
}