/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Find a value in env
*/
#include "mysh.h"

char *find_in_env(env_t *env, char *key)
{
    for (env_t *temp = env; temp; temp = temp->next) {
        if (!my_strcmp(key, temp->key)) {
            return my_strdup(temp->value);
        }
    }
    return (char *) 0;
}

char *find_in_env_without_dup(env_t *env, char *key)
{
    for (env_t *temp = env; temp; temp = temp->next) {
        if (!my_strcmp(key, temp->key)) {
            return temp->value;
        }
    }
    return (char *) 0;
}

/*
char *find_in_env(char **env, char *key)
{
    char **line = (char **) 0;
    char *to_return = (char *) 0;
    int found = 0;

    for (int i = 0; !found && env[i]; ++i) {
        line = my_strsplit(env[i], '=');
        if (line && line[1] && !my_strcmp(line[0], key)) {
            to_return = my_strdup(line[1]);
        }
        my_free_word_array(line);
    }
    return to_return;
}
*/
