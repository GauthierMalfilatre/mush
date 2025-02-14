/*
** EPITECH PROJECT, 2025
** MINISHELL1
** File description:
** Transform char ** into likend list of char *
*/
#include "mysh.h"

void add_env(env_t **env, char *key, char *value)
{
    env_t *new = malloc(sizeof(env_t));

    new->key = 0;
    new->value = 0;
    if (key)
        new->key = my_strdup(key);
    if (value)
        new->value = my_strdup(value);
    new->prev = 0;
    new->next = *env;
    if (*env) {
        (*env)->prev = new;
    }
    *env = new;
    return;
}

env_t *env_to_list(char **env)
{
    env_t *new = 0;
    char **line = (char **) 0;

    for (int i = 0; env[i]; ++i) {
        line = my_strsplit(env[i], '=');
        if (line && line[0]) {
            add_env(&new, line[0], &env[i][my_strlen(line[0]) + 1]);
        }
        my_free_word_array(line);
    }
    reverse_env(&new);
    return new;
}

static int len_list(env_t *list)
{
    int count = 0;

    for (env_t *temp = list; temp; temp = temp->next) {
        ++count;
    }
    return count;
}

static char *build_envline(env_t *env)
{
    char *temp = my_stradd(env->key, "=");
    char *line = my_stradd(temp, env->value);

    free(temp);
    return line;
}

char **list_to_env(env_t *list)
{
    int len = len_list(list);
    char **env = malloc(sizeof(env_t) * (len + 1));
    int i = 0;

    if (!env) {
        return (char **) 0;
    }
    for (env_t *temp = list; temp; temp = temp->next) {
        env[i] = build_envline(temp);
        i++;
    }
    env[len] = (char *) 0;
    return env;
}

void print_env(env_t *list)
{
    for (env_t *temp = list; temp; temp = temp->next) {
        if (temp->value)
            my_printf("%s=%s\n", temp->key, temp->value);
        else
            my_printf("%s=\n", temp->key);
    }
}

static void del_node(env_t **head, env_t *env)
{
    free(env->key);
    free(env->value);
    if (env->prev) {
        env->prev->next = env->next;
    } else {
        *head = env->next;
    }
    if (env->next) {
        env->next->prev = env->prev;
    }
    free(env);
}

void del_env(env_t **list, char *key)
{
    for (env_t *temp = *list; temp; temp = temp->next) {
        if (!my_strcmp(key, temp->key)) {
            del_node(list, temp);
            return;
        }
    }
    return;
}
