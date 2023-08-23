#include "main.h"
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