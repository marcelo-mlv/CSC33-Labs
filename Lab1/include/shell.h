#include <stdio.h>

#include <cmd.h>

/**
 * @brief Shell Main Loop.
 * 
 * 
 */
void main_loop() {

    printf("cmd> ");
    
    char *cmd    = get_cmd();
    char ** args = separate_args(cmd);
    parse_cmd(args);
    
    free(args);
    free(cmd);
}
