/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** my_cd.c
*/
#include "mysh.h"

static int catch_error(data_t *data, char **line)
{
    int len = my_len_word_array(line);

    if (len > 2) {
        data->last_code = 1;
        return 1 + 0 * mini_fprintf(2, "cd: Too many arguments.\n");
    }
    if (len < 2) {
        return 0;
    }
    if (!my_strcmp(line[1], "-") && !data->last_dir) {
        data->last_code = 1;
        mini_fprintf(2, ": No such file or directory.\n");
        return 1;
    }
    return 0;
}

void my_cd(data_t *data, char **line)
{
    char *to_change = line[1];
    int len = my_len_word_array(line);

    if (catch_error(data, line))
        return;
    if (len > 1 && !my_strcmp(line[1], "-"))
        to_change = data->last_dir;
    if (my_len_word_array(line) < 2 || (len > 1 && !my_strcmp(to_change, "~")))
        to_change = find_in_env_without_dup(data->env, "HOME");
    if (chdir(to_change) == -1) {
        mini_fprintf(2, "%s: %s.\n", line[1], strerror(errno));
        data->last_code = 1;
    } else {
        ifree(data->last_dir);
        data->last_dir = my_strdup(data->current_dir);
        free(data->current_dir);
        data->current_dir = getcwd(0, 0);
        data->last_code = 0;
    }
}
