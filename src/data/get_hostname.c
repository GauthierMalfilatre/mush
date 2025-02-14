/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Get hostname for prompt
*/
#include "mysh.h"

char *get_hostname(void)
{
    FILE *fp = fopen("/etc/hostname", "r");
    char *buffer = (char *) 0;
    size_t size = 0;
    char *to_return;

    if (getline(&buffer, &size, fp) == -1) {
        return my_strdup("HOST");
    }
    fclose(fp);
    to_return = my_strndup(buffer, my_strlen(buffer) - 1);
    free(buffer);
    return to_return;
}
