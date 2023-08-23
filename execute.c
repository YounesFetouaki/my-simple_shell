#include "main.h"
/**
 * execute - Function to execute the arguments
 * @args: The arguments parsed from the input line
 *
 * Return: The result of the corresponding function or launch function
 */
int execute(char **args)
{
	int i;

	if (args[0] == NULL) /* If there are no arguments */
	{
		return (1); /* Return 1 to continue the loop in main function */
	}
	/* Loop through the built-in commands array */
	for (i = 0; i < num_built_ins(); i++)
	{/* If the first argument matches a built-in command name */
		if (strcmp(args[0], built_in_str[i]) == 0)
		{/* Call the corresponding function and return its result */
			return ((*built_in_func[i])(args));
		}
	}
	/* If no built-in command matches, launch the program and return its result */
	return (launch(args));
}
