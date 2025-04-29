#include <stdio.h>

/**
 * @brief Print the args vector for debugging.
 * 
 * @param args Command arguments.
 */
void print_args(char **args) {
    printf("Arguments vector:\n");
    for (int i = 0; args[i] != NULL; i++) {
        printf("args[%d]: %s\n", i, args[i]);
    }
    printf("End of arguments.\n");
}
