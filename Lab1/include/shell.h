#include <stdio.h>

#include <cmd.h>

/**
 * @brief Shell Main Loop.
 * 
 * Called only by main().
 */
void main_loop() {

    printf("cmd> ");

    int   status;
    char*    cmd;
    char**  args;
    
    do {
        cmd    = get_cmd();
        args   = separate_args(cmd);
        status = cmd_execute(args);

        free(args);
        free(cmd);
    } while(status);
}
