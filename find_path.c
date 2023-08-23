#include "main.h"
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