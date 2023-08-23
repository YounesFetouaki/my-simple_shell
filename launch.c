#include "main.h"
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