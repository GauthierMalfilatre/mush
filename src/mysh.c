/*
** EPITECH PROJECT, 2025
** MYSH
** File description:
** Minishell1 main file.
*/
#include "mysh.h"

static int intercept(data_t *data, char **line)
{
    if (!my_strcmp(line[0], "cd")) {
        my_cd(data, line);
        return 1;
    }
    if (!my_strcmp(line[0], "env")) {
        print_env(data->env);
        return 1;
    }
    if (!my_strcmp(line[0], "setenv")) {
        add_to_env(data, line);
        return 1;
    }
    if (!my_strcmp(line[0], "unsetenv")) {
        del_to_env(&data->env, line);
        return 1;
    }
    return 0;
}

void process_line(data_t *data, char **line, char **line2, int is_pipe)
{
    pid_t pid;
    int exitstatus;

    if (intercept(data, line))
        return;
    pid = fork();
    switch (pid) {
    case -1:
        exit(84);
    case 0:
        process_child(data, line, line2, is_pipe);
        break;
    default:
        process_parent(data, is_pipe, &exitstatus, pid);
        break;
    }
}

void pre_process_line(data_t *data, char *line, char **line2, int is_pipe)
{
    char **temp = (char **) 0;

    temp = my_str_to_word_array(line);
    if (!temp || !temp[0]) {
        my_free_word_array(temp);
        return;
    }
    replace_with_env(data, temp);
    process_line(data, temp, line2, is_pipe);
    my_free_word_array(temp);
    return;
}

static int decide_piping(char **temp, int index)
{
    if (!index) {
        return BEFORE;
    }
    if (!temp[index + 1]) {
        return AFTER;
    }
    return BETWEEN;
}

static void reinit_fd(data_t *data)
{
    int extistatus;

    for (int i = data->current_pipefd - 1; i > 0 && data->pids[i]; i--) {
        waitpid(data->pids[i], &extistatus, 0);
        data->last_code = handle_signal(extistatus);
    }
    for (int i = 0; i < MAXPIPE; i++) {
        data->pids[i] = 0;
    }
    data->current_pipefd = 0;
    return;
}

static int count(char *str, char c)
{
    int length = 0;

    for (int i = 0; str[i]; i++) {
        if (str[i] == c) {
            length++;
        }
    }
    return length;
}

void deal_pipes(data_t *data, char *line, char **line2)
{
    int is_pipe = count(line, '|');
    char **temp = my_strsplit(line, '|');

    if (is_pipe && (my_len_word_array2(temp) < is_pipe + 1)) {
        my_errstr("Invalid null command.\n");
        return;
    }
    for (int i = 0; temp[i]; i++) {
        if (is_pipe)
            pipe(data->pipefd[data->current_pipefd]);
        pre_process_line(data, temp[i], line2,
            is_pipe ? decide_piping(temp, i) : NO);
        if (is_pipe)
            data->current_pipefd++;
    }
    if (is_pipe)
        reinit_fd(data);
    my_free_word_array(temp);
    return;
}

static int show_prompt(data_t *data)
{
    if (isatty(0)) {
        my_printf("[%s%d"WHITE"] ", data->last_code ? RED : GREEN,
            data->last_code);
        my_printf(BPROMPT);
    }
    return 1;
}

void mysh(data_t *data)
{
    char *buffer = (char *) 0;
    size_t len = 0;
    char **line = (char **) 0;

    while (show_prompt(data) && getline(&buffer, &len, stdin) != -1) {
        if (!isatty(0) && buffer[0] == '\n')
            break;
        if (isatty(0) && buffer[0] == '\n') {
            continue;
        }
        if (!my_strcmp("exit\n", buffer) || !my_strcmp("exit", buffer)) {
            break;
        }
        line = my_strsplit(buffer, ';');
        for (int i = 0; line[i]; i++)
            deal_pipes(data, line[i], line);
        my_free_word_array(line);
    }
    free(buffer);
    return;
}

int main(int argc, char *const *argv, char **env)
{
    int exitcode = 0;
    data_t *data = init_data(env);

    (void)argc;
    (void)argv;
    mysh(data);
    exitcode = data->last_code;
    destroy_data(data);
    return exitcode;
}
