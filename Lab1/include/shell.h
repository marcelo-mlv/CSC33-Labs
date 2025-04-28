#include <stdio.h>

#include <cmd.h>

void main_loop() {

    printf("cmd> ");
    
    char *cmd = get_cmd();
    
    parse_cmd(cmd);

}
