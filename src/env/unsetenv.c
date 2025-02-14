/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Unset value in env
*/
#include "mysh.h"

void del_to_env(env_t **env, char **line)
{
    char *key = line[1];

    if (my_len_word_array(line) < 2) {
        mini_fprintf(2, "unsetenv: Too few arguments.\n");
    }
    del_env(env, key);
}
