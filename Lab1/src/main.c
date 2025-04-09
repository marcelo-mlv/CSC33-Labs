#include <stdio.h>
#include <cmd.h>

int main() {

    printf("Welcome to the miniature-shell.\n");
    
    printf("cmd> ");
    char *cmd = get_cmd();

    return 0;
}
