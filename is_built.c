#include "main.h"

/**
 * num_built_ins - Function to get the number of built-in commands
 *
 * Return: The number of built-in commands
 */
int num_built_ins(void)
{
	/* The number of built-in commands */
	char *built_in_str[] = {
		"exit",
		"env"
	};

	return (sizeof(built_in_str) / sizeof(char *));
}
