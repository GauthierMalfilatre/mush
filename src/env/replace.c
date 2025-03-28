/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Replace $... with env
*/
#include "mysh.h"

static char *strdup_replace(char *str, char *to_replace, char *to_put)
{
    char *new = (char *) 0;
    int offset = 0;

    if (!str) {
        return my_strdup(str);
    }
    new = malloc(sizeof(char *) * (my_strlen(str)
        - my_strlen(to_replace) + my_strlen(to_put) + 1));
    offset = my_strstr(str, to_replace) - str;
    my_strncpy(new, str, offset);
    my_strcat(new, to_put);
    my_strcat(new, &str[offset + my_strlen(to_replace)]);
    return new;
}

static void sub(data_t *data, char *line, char **command)
{
    char *temp = (char *) 0;

    for (int j = 0; line[j]; j++) {
        if (line[j] == '$' && (j <= 0 || (j > 0 && line[j - 1] != '\\'))) {
            temp = find_in_env(data->env, &line[j + 1]);
            ifree(*command);
            *command = strdup_replace(line, &line[j], temp);
            free(temp);
        }
    }
    return;
}

void replace_with_env(data_t *data, char **commandline)
{
    for (int i = 0; commandline[i]; i++) {
        if (!is_char_in(commandline[i], '$')) {
            continue;
        }
        sub(data, commandline[i], &commandline[i]);
    }
    return;
}
