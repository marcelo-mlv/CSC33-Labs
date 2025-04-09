#include <malloc.h>

char* get_cmd() {
    char *cmd = (char *)malloc(100);
    if (cmd == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    scanf("%s", cmd);

    return cmd;
}

