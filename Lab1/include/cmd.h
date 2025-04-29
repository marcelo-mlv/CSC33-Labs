#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

#define ARG_BUFSIZE 64

// Forward declaration of the launch function
int launch(char **args);

/**
 * @brief User Input Read As Command.
 * 
 * 
 */
char* get_cmd() {
    char *cmd = NULL;
    size_t bufsize = 0;

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

/**
 * @brief Command String Split Into Arguments.
 * 
 * @param cmd Command String.
 * @return char** Array of Arguments.
 */
char** separate_args(char *cmd) {
    int bufsize = ARG_BUFSIZE;
    char **args = (char **)malloc(ARG_BUFSIZE * sizeof(char*));

    if(args == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    int arg_index = 0;
    char *arg = strtok(cmd, " \t\r\n\a");
    while(arg != NULL) {
        args[arg_index++] = arg;
        arg_index++;
        
        if(arg_index >= bufsize) {
            bufsize += ARG_BUFSIZE;
            args = (char **)realloc(args, bufsize * sizeof(char*));
            if(args == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                exit(1);
            }
        }
        arg = strtok(NULL, " \t\r\n\a");
    }
    
    args[arg_index] = NULL;
    return args;
}

/**
 * @brief Command Parser.
 * 
 * @param args Command Arguments.
 * @return void
 */
int launch(char **args)
{
    pid_t pid;
    int status;
    int in_redirect = -1, out_redirect = -1;
    char *input_file = NULL, *output_file = NULL;

    // Check for redirection operators
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            input_file = args[i + 1];
            in_redirect = i;
        } else if (strcmp(args[i], ">") == 0) {
            output_file = args[i + 1];
            out_redirect = i;
        }
    }

    // Remove redirection operators and files from args
    if (in_redirect != -1) {
        args[in_redirect] = NULL;
    }
    if (out_redirect != -1) {
        args[out_redirect] = NULL;
    }

    pid = fork();
    if (pid == 0) {
        // Child process
        if (input_file) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in == -1) {
                perror("Input redirection failed");
                exit(1);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (output_file) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1) {
                perror("Output redirection failed");
                exit(1);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        if (execv(args[0], args) == -1) {
            perror("launch");
        }
        exit(1);
    } else if (pid < 0) {
        // Fork failed
        perror("launch");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
            printf("cmd> ");
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
 * @brief Command Parser.
 * 
 * @param args Command Arguments.
 * @return void
 */
int cmd_execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    return launch(args);
}
