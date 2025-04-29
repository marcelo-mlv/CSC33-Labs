#include <malloc.h>
#include <string.h>

char* get_cmd() {
    char *cmd = NULL;
    __ssize_t bufsize = 0;

    if(getline(&cmd, &bufsize, stdin) == -1) {
        if(feof(stdin)) {
            exit(0);
        } else {
            perror("getcmd");
            exit(1);
        }
    }

    return cmd;
}

char** separate_args(char *cmd) {
    char **args = (char **)malloc(10*sizeof(char*));
    if(args == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(cmd);
        return NULL;
    }

    int arg_index = 0;
    char *token = strtok(cmd, " ");
    while(token != NULL && arg_index < 10) {
        args[arg_index++] = token;
        token = strtok(NULL, " ");
    }
    args[arg_index] = NULL;
    
    return args;
}

void parse_cmd(char **args) {

    if(strcmp(args[0], "exit") == 0) {
        printf("Exiting shell...\n");
    }
    else printf("Command not found: \"%s\"\n", args[0]);

    return;
}
