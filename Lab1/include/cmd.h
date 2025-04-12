#include <malloc.h>
#include <string.h>

char* get_cmd() {
    char *cmd = (char *)malloc(100*sizeof(char));
    if (cmd == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    scanf("%s", cmd);

    return cmd;
}

char** separate_args(char *cmd) {
    char **args = (char **)malloc(10*sizeof(char*));
    if (args == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    for(int i = 0; cmd[i] != '\0'; i++) {
        if(cmd[i] == ' ') {
            cmd[i] = '\0';
            args[i] = &cmd[i+1];
        } else {
            args[i] = &cmd[i];
        }
    }
    return args;
}

void parse_cmd(char *cmd) {
    char** args = separate_args(cmd);
    if(strcmp(args[0], "exit") == 0) {
        printf("Exiting shell...\n");
    }
    else printf("Command not found: \"%s\"\n", args[0]);
    
    free(args);
    free(cmd);
    return;
}
