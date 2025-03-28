/*
** EPITECH PROJECT, 2024
** MINISHELL1
** File description:
** Header file for minishell1
*/
#ifndef MYSH_H
    #define MYSH_H
    #include "my.h"
    #include "liblifo.h"
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
    #define MAXPIPE 32
    #define PROMPT "$> "
    #define VIOLET "\x1b[38;2;126;0;141m"
    #define CYAN "\x1b[38;2;43;255;255m"
    #define WHITE "\x1b[1;37m"
    #define GREEN "\e[1;32m"
    #define RED "\e[1;31m"
    #define RP data->username, data->host, data->current_dir
    #define BPROMPT CYAN"%s@%s"WHITE":"VIOLET"%s"WHITE"$ ", RP
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
    int pids[MAXPIPE];
    char *current_dir;
    char *last_dir;
    int pipefd[MAXPIPE][2];
    int current_pipefd;
} data_t;

typedef struct redirect_s {
    char *op;
    char *file;
    char **command;
    struct redirect_s *next;
} redirect_t;

enum pos_e {
    NO,
    BEFORE,
    AFTER,
    BETWEEN,
};

/* AST */
typedef enum ast_e {
    AST_COMMAND,
    AST_PIPE,
    AST_SEMICOLON,
    AST_REDIRECT_IN,
    AST_REDIRECT_OUT,
    AST_REDIRECT_ININ,
    AST_REDIRECT_OUTOUT,
} ast_e_t;

typedef struct {
    char *token;
    ast_e_t type;
} token_map_t;

typedef struct ast_node_s {
    ast_e_t type;
    char *value;
    struct ast_node_t *left;
    struct ast_node_t *right;
} ast_node_t;

extern const token_map_t token_map[];

ast_node_t *create_ast_node(ast_e_t type, char *value);
void destroy_ast_node(ast_node_t *node);
void destroy_ast(ast_node_t *root);
int get_token_type(const token_map_t *token_map, char *token);

ast_node_t *build_ast(const token_map_t *token_map, char **tokens);
ast_node_t *handle_operator(ast_node_t *last_operator,
    ast_node_t *current_command, ast_e_t type, char *token);
ast_node_t *handle_command(ast_node_t *current_command, char *token);
/* End of AST */

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

void replace_with_env(data_t *data, char **commandline);

/* Operators */
int is_single_right(char **line);
int *get_fds(char **line);

redirect_t *build_redirections(char *line);

char **special_dup_warray(char **warray);

void pipe_before(data_t *data);
void pipe_after(data_t *data);

/* Other */
void process_child(data_t *data, char **line, char **line2, int is_pipe);
void process_parent(data_t *data, int is_pipe, int *exitstatus, int pid);

void my_cd(data_t *data, char **line);

int handle_signal(int exitstatus);

int is_line_empty(char *line);

int my_len_word_array2(char **array);

// AST
int command_line_to_ast(data_t *data, char **line);

#endif
