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

int main(int ac, char **av)
{
    char *test_string = av[1];
    
    // Test echo_n with n = 1
    printf("Testing echo_n with n = 1:\n");
    if (echo_n(test_string, 1) == 0) {
        printf("Successfully echoed string with n = 1!\n\n");
    } else {
        printf("Failed to echo string with n = 1!\n\n");
    }
    
    // Test echo_n with n = 2
    printf("Testing echo_n with n = 2:\n");
    if (echo_n(test_string, 2) == 0) {
        printf("Successfully echoed string with n = 2!\n\n");
    } else {
        printf("Failed to echo string with n = 2!\n\n");
    }
}