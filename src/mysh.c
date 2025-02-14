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

void process_line(data_t *data, char **line)
{
    pid_t pid;
    int exitstatus;

    if (intercept(data, line)) {
        return;
    }
    pid = fork();
    switch (pid) {
    case -1:
        my_printf("ERROR");
        exit(84);
    case 0:
        process_child(data, line);
        break;
    default:
        waitpid(pid, &exitstatus, 0);
        data->last_code = handle_signal(exitstatus);
        break;
    }
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
        line = my_str_to_word_array(buffer);
        process_line(data, line);
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
