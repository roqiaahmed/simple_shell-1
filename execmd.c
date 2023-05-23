#include "main.h"

/**
 * execmd - Executes a command with arguments
 * @argv: An array of strings containing the command and its arguments
 */
void execmd(char **argv)
{
char *command = NULL, *path = NULL;

if (argv)
{
command = argv[0];
path = get_location(command);
if (execve(path, argv, NULL) == -1)
{
perror("Error:");
};
}
}

