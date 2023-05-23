#include "main.h"

/**
 * print_environment - Prints all environment variables
 */
void print_environment()
{
extern char **environ;
char **envp = environ;
while (*envp != NULL)
{
printf("%s\n", *envp);
envp++;
}
}
/**
 * execute_command - Executes a command in a new child process
 * @argv: An array of strings containing the command and its arguments
 */
void execute_command(char **argv)
{
pid_t pid;
pid = fork();
if (pid == -1)
{
perror("tsh: fork error");
exit(-1);
}
else if (pid == 0)
{
execmd(argv);
exit(0);
}
else
{
wait(NULL);
}
}
/**
 * main - Entry point for the tsh shell program
 * @argc: The number of arguments passed to the program
 * @argv: An array of strings containing the arguments passed to the program
 *
 * Return: 0 on success, -1 on failure
 */
int main(int argc, char **argv)
{
char *buff = NULL, *buff_copy = NULL, *token, *prompt = "$ ";
size_t buff_size = 0;
ssize_t characters;
const char *delims = " \n";
int i, token_num = 0;
(void)argc;
while (1)
{
printf("%s", prompt);
characters = getline(&buff, &buff_size, stdin);
if (characters == -1)
{
printf("Exiting shell....\n");
return (-1);
}
buff_copy = malloc(sizeof(char) * characters);
if (buff_copy == NULL)
{
perror("tsh: memory allocation error");
return (-1);
}
strcpy(buff_copy, buff);
token = strtok(buff, delims);
while (token != NULL)
{
token_num++;
token = strtok(NULL, delims);
}
token_num++;
argv = malloc(sizeof(char *) * token_num);
token = strtok(buff_copy, delims);
for (i = 0; token != NULL; i++)
{
argv[i] = malloc(sizeof(char) * strlen(token));
strcpy(argv[i], token);
token = strtok(NULL, delims);
}
argv[i] = NULL;
if (strcmp(argv[0], "exit") == 0)
break;
else if (strcmp(argv[0], "env") == 0)
{
print_environment();
}
else
{
execute_command(argv);
}
}
free(buff);
free(buff_copy);
return (0);
}

