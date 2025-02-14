/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Set value in env
*/
#include "mysh.h"

static int is_alpha(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static int is_num(char c)
{
    return (c >= '1' && c <= '9');
}

static int is_alphanum(char c)
{
    return (is_alpha(c) || is_num(c) || c == '_');
}

static int is_str_alphanum(char *str)
{
    for (int i = 0; i[str]; ++i) {
        if (!is_alphanum(i[str])) {
            return 0;
        }
    }
    return 1;
}

static int catch_error(char *key)
{
    if (!is_alpha(key[0])) {
        mini_fprintf(2, "setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    if (!is_str_alphanum(key)) {
        mini_fprintf(2,
            "setenv: Variable name must contain alphanumeric characters.\n");
        return 1;
    }
    return 0;
}

void add_or_update(env_t **env, char *key, char *value)
{
    for (env_t *temp = *env; temp; temp = temp->next) {
        if (!my_strcmp(key, temp->key)) {
            ifree(temp->value);
            temp->value = my_strdup(value);
            return;
        }
    }
    add_env(env, key, value);
    return;
}

void add_to_env(data_t *data, char **line)
{
    char *key = line[1];
    char *value = my_len_word_array(line) > 2 ? line[2] : (char *) 0;

    if (my_len_word_array(line) > 3) {
        mini_fprintf(2, "setenv: Too many arguments.\n");
        data->last_code = 1;
        return;
    }
    if (!key && !value) {
        print_env(data->env);
        return;
    }
    if (catch_error(key)) {
        data->last_code = 1;
        return;
    }
    reverse_env(&data->env);
    add_or_update(&data->env, key, value);
    reverse_env(&data->env);
}
