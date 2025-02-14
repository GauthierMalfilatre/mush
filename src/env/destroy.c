/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Transform char ** into likend list of char *
*/
#include "mysh.h"

void destroy_env(env_t *list)
{
    if (list->next) {
        destroy_env(list->next);
    }
    if (list->value)
        ifree(list->value);
    ifree(list->key);
    ifree(list);
    return;
}
