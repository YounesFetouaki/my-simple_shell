#ifndef MAIN_H
#define MAIN_H
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
int num_built_ins(void);
/* Array of built-in commands and their corresponding functions */
extern char *built_in_str[];
extern int (*built_in_func[])(char **);
/* The number of built-in commands */
char *built_in_str[] = {
	"exit",
	"env"
};
int (*built_in_func[]) (char **) = {
	&built_in_exit,
	&built_in_env
};

#endif
