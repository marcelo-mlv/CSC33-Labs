#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

#include <debug.h>

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
        args[arg_index] = arg;
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
 * @brief Provides functionality to execute commands with optional input and output redirection.
 *
 * This header defines the `launch` function, which is responsible for parsing command-line arguments,
 * handling input/output redirection, and executing the specified command in a child process.
 * It supports redirection operators `<` for input and `>` for output.
 * 
 * @param args An array of strings representing the command and its arguments.
 * @return int Returns 1 on success, or -1 on failure.
 *
 * Usage:
 * - The function takes an array of strings (`args`) representing the command and its arguments.
 * - Redirection operators and their corresponding file paths should be included in the `args` array.
 * - The function handles the redirection internally and executes the command.
 *
 * Example:
 * ```c
 * char *args[] = {"/bin/ls", "-l", ">", "output.txt", NULL};
 * launch(args);
 * ```
 *
 * @note The function uses `fork`, `execv`, and `dup2` for process creation and redirection.
 *       It also waits for the child process to complete before returning.
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

        // Ensure the first argument points to the program name
        if (args[0] != NULL) {
            //print_args(args);
            if (execv(args[0], args) == -1) {
                perror("launch");
            }
        } else {
            fprintf(stderr, "Error: No program specified to execute.\n");
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
 * @brief Command Execute.
 * 
 * @param args Command Arguments.
 * @return int 
 */
int cmd_execute(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "prog") == 0) {
        printf("cmd> ");
        return 1;
    }

    return launch(args);
}
