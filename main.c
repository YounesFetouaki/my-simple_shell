#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"
extern char **environ;

/* Function prototypes */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int launch(char **args);
char *find_path(char *command);
int built_in_exit(char **args);
int built_in_env(char **args);

/* Array of built-in commands and their corresponding functions */
char *built_in_str[] = {
  "exit",
  "env"
};

int (*built_in_func[]) (char **) = {
  &built_in_exit,
  &built_in_env
};

/* The number of built-in commands */
int num_built_ins() {
  return sizeof(built_in_str) / sizeof(char *);
}

/* Main function */
int main(void)
{
  char *line; /* The input line */
  char **args; /* The arguments parsed from the input line */
  int status; /* The status of the execution */

  do {
    printf("$ "); /* Print the prompt */
    line = read_line(); /* Read the input line */
    args = split_line(line); /* Split the input line into arguments */
    status = execute(args); /* Execute the arguments */

    free(line); /* Free the allocated memory for the input line */
    free(args); /* Free the allocated memory for the arguments */
  } while (status); /* Loop until the status is zero */

  return EXIT_SUCCESS;
}

/* Function to read a line from stdin */
char *read_line(void)
{
  char *line = NULL; /* The input line */
  size_t bufsize = 0; /* The buffer size, initialized to zero */
  ssize_t nread; /* The number of characters read */

  nread = getline(&line, &bufsize, stdin); /* Read a line from stdin */

  if (nread == -1) { /* If there is an error or EOF */
    if (feof(stdin)) { /* If it is EOF */
      printf("\n"); /* Print a new line */
      exit(EXIT_SUCCESS); /* Exit with success */
    }
    else { /* If it is an error */
      perror("read_line"); /* Print the error message */
      exit(EXIT_FAILURE); /* Exit with failure */
    }
  }

  return line; /* Return the input line */
}

/* Function to split a line into arguments */
char **split_line(char *line)
{
  int bufsize = BUFSIZE; /* The buffer size, initialized to a constant value */
  int position = 0; /* The current position in the buffer */
  char **tokens = malloc(bufsize * sizeof(char*)); /* The array of tokens (arguments) */
  char *token; /* The current token */

  if (!tokens) { /* If the memory allocation fails */
    fprintf(stderr, "split_line: allocation error\n"); /* Print the error message */
    exit(EXIT_FAILURE); /* Exit with failure */
  }

  token = strtok(line, DELIM); /* Get the first token from the line */

  while (token != NULL) { /* While there are more tokens */
    tokens[position] = token; /* Store the token in the array */
    position++; /* Increment the position */

    if (position >= bufsize) { /* If the buffer is full */
      bufsize += BUFSIZE; /* Increase the buffer size by a constant value */
      tokens = realloc(tokens, bufsize * sizeof(char*)); /* Reallocate more memory for the array */

      if (!tokens) { /* If the memory allocation fails */
        fprintf(stderr, "split_line: allocation error\n"); /* Print the error message */
        exit(EXIT_FAILURE); /* Exit with failure */
      }
    }

    token = strtok(NULL, DELIM); /* Get the next token from the line */
  }

  tokens[position] = NULL; /* Terminate the array with a NULL pointer */

  return tokens; /* Return the array of tokens */
}

/* Function to execute the arguments */
int execute(char **args)
{
  int i;

  if (args[0] == NULL) { /* If there are no arguments */
    return 1; /* Return 1 to continue the loop in main function */
  }

  for (i = 0; i < num_built_ins(); i++) { /* Loop through the built-in commands array */
    if (strcmp(args[0], built_in_str[i]) == 0) { /* If the first argument matches a built-in command name */
      return (*built_in_func[i])(args); /* Call the corresponding function and return its result */
    }
  }

  return launch(args); /* If no built-in command matches, launch the program and return its result */
}

/* Function to launch a program */
int launch(char **args)
{
  pid_t pid; /* The process ID */
  int status; /* The status of the execution */

  pid = fork(); /* Fork a child process */

  if (pid == 0) { /* If it is the child process */
    char *path; /* The path of the executable */

    path = find_path(args[0]); /* Find the path of the executable */

    if (path == NULL) { /* If the path is not found */
      fprintf(stderr, "%s: command not found\n", args[0]); /* Print the error message */
      exit(EXIT_FAILURE); /* Exit with failure */
    }

    if (execve(path, args, environ) == -1) { /* Execute the program with the arguments and the environment */
      perror("launch"); /* Print the error message */
      exit(EXIT_FAILURE); /* Exit with failure */
    }
  }
  else if (pid < 0) { /* If the fork fails */
    perror("launch"); /* Print the error message */
    exit(EXIT_FAILURE); /* Exit with failure */
  }
  else { /* If it is the parent process */
    do {
      waitpid(pid, &status, WUNTRACED); /* Wait for the child process to change state */
    } while (!WIFEXITED(status) && !WIFSIGNALED(status)); /* Loop until the child process exits normally or by a signal */
  }

  return 1; /* Return 1 to continue the loop in main function */
}

/* Function to find the path of an executable */
char *find_path(char *command)
{
  struct stat st; /* The stat structure to check if the file exists and is executable */

  /* Check if the provided command is an absolute path */
  if (command[0] == '/') {
    if (stat(command, &st) == 0 && st.st_mode & S_IXUSR) { /* If the file exists and is executable by the user */
      return strdup(command); /* Return the command as the full path of the executable */
    }
    return NULL; /* Return NULL if the absolute path is not executable */
  }

  char *path = getenv("PATH"); /* Get the value of the PATH environment variable */

  if (path == NULL) { /* If the PATH is not set */
    return NULL; /* Return NULL */
  }

  path = strdup(path); /* Duplicate the PATH value */

  if (path == NULL) { /* If the memory allocation fails */
    return NULL; /* Return NULL */
  }

  char *token = strtok(path, ":"); /* Get the first token (directory) in the PATH */

  while (token != NULL) { /* While there are more tokens (directories) in the PATH */
    char *buffer = malloc(strlen(token) + strlen(command) + 2); /* Allocate memory for the buffer */

    if (buffer == NULL) { /* If the memory allocation fails */
      free(path); /* Free the allocated memory for the PATH value */
      return NULL; /* Return NULL */
    }

    strcpy(buffer, token); /* Copy the token (directory) to the buffer */
    strcat(buffer, "/"); /* Append a slash to the buffer */
    strcat(buffer, command); /* Append the command to the buffer */

    if (stat(buffer, &st) == 0 && st.st_mode & S_IXUSR) { /* If the file exists and is executable by the user */
      free(path); /* Free the allocated memory for the PATH value */
      return buffer; /* Return the buffer as the full path of the executable */
    }

    free(buffer); /* Free the allocated memory for the buffer */

    token = strtok(NULL, ":"); /* Get the next token (directory) in the PATH */
  }

  free(path); /* Free the allocated memory for the PATH value */

  return NULL; /* Return NULL if no path is found */
}

/* Function to exit from the shell */
int built_in_exit(char **args)
{
  return 0; /* Return 0 to terminate the loop in main function */
}

/* Function to print the environment variables */
int built_in_env(char **args)
{
  int i;

  for (i = 0; environ[i] != NULL; i++) { /* Loop through the environ array */
    printf("%s\n", environ[i]); /* Print each environment variable with a new line */
  }

  return 1; /* Return 1 to continue the loop in main function */
}