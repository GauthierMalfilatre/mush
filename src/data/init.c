/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Init data_t struct
*/
#include "mysh.h"

data_t *init_data(char **env)
{
    data_t *new = malloc(sizeof(data_t));

    if (!new) {
        return (data_t *) 0;
    }
    new->env = env_to_list(env);
    new->username = find_in_env(new->env, "USER");
    new->host = (char *) 0;
    new->last_dir = (char *) 0;
    new->current_dir = getcwd(0, 0);
    new->last_code = 0;
    return new;
}

void destroy_data(data_t *data)
{
    destroy_env(data->env);
    ifree(data->username);
    ifree(data->last_dir);
    ifree(data->current_dir);
    ifree(data);
    return;
}
