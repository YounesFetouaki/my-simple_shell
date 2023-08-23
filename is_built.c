#include "main.h"

/**
 * num_built_ins - Function to get the number of built-in commands
 *
 * Return: The number of built-in commands
 */
int num_built_ins(void)
{
	char *built_in_str[] = {
		"exit",
		"env"
	};
	int (*built_in_func[]) (char **) = {
		&built_in_exit,
		&built_in_env
	};

	return (sizeof(built_in_str) / sizeof(char *));
}
