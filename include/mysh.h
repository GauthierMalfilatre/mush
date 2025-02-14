/*
** EPITECH PROJECT, 2024
** MINISHELL1
** File description:
** Header file for minishell1
*/
#ifndef MYSH_H
    #define MYSH_H
    #include "my.h"
    #include <errno.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <grp.h>
    #include <fcntl.h>
    #include <elf.h>
    #include <sys/stat.h>
    #include <sys/wait.h>
    #include <sys/types.h>
    #include <signal.h>
    #define PROMPT "$> "
    #define RP data->last_code, data->username, data->host, data->current_dir
    #define BPROMPT "[%d] %s@%s:%s$ ", RP
    #define ERRORCODE -1
    #define OKCODE 0
    #define EXITCODE 69

typedef struct env_s {
    char *key;
    char *value;
    struct env_s *next;
    struct env_s *prev;
} env_t;

typedef struct data_s {
    int last_code;
    env_t *env;
    char *username;
    char *host;
    char *current_dir;
    char *last_dir;
} data_t;

/* Data */
data_t *init_data(char **env);
char *get_hostname(void);
void destroy_data(data_t *data);

void pathfinder(data_t *data, char *tampon, char *command);

/* Env */
env_t *env_to_list(char **env);
char **list_to_env(env_t *list);
char *find_in_env(env_t *env, char *key);
char *find_in_env_without_dup(env_t *env, char *key);
void destroy_env(env_t *list);

void reverse_env(env_t **head);

void add_env(env_t **env, char *key, char *value);
void del_env(env_t **list, char *key);
void print_env(env_t *list);

void add_to_env(data_t *data, char **line);
void del_to_env(env_t **env, char **line);

void process_child(data_t *data, char **line);

void my_cd(data_t *data, char **line);

/* Signal */
void handle_signal(int exitstatus);

#endif
