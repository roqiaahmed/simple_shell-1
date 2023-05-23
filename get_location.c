#include "main.h"

/**
 * get_location - Finds the location of a command in the PATH
 * @command: The command to search for
 *
 * Return: the full path to the command, or NULL
 */
char *get_location(char *command)
{
char *path, *path_copy, *token, *full_path;
int command_num, token_num;
struct stat buff;

path = getenv("PATH");
if (path)
{
path_copy = strdup(path);
token = strtok(path_copy, ":");
while (token != NULL)
{
command_num = strlen(command);
token_num = strlen(token);
full_path = malloc(command_num + token_num + 2);
strcpy(full_path, token);
strcat(full_path, "/");
strcat(full_path, command);
strcat(full_path, "\0");
if (stat(full_path, &buff) == 0)
{
free(path_copy);
return (full_path);
}
else
{
free(full_path);
token = strtok(NULL, ":");
}
}
free(path_copy);
if (stat(command, &buff) == 0)
{
return (command);
}
return (NULL);
}
return (NULL);
}

