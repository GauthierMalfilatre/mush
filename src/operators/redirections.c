/*
** EPITECH PROJECT, 2025
** MYSH
** File description:
** Build redirections tab
*/
#include "mysh.h"

/*
static int is_op(char *word)
{
    char *ops[] = {"<", "<<", ">", ">>"};

    for (int i = 0; i < 4; i++) {
        if (!my_strcmp(word, ops[i])) {
            return 1;
        }
    }
    return 0;
}
*/
redirect_t *build_redirections(char *line)
{
    redirect_t *to_ret = 0;
    char command[256];
    char current_op[2];
    int index_c_op = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '<' || line[i] == '>') {
            current_op[index_c_op] = line[i];
            index_c_op++;
            continue;
        }
        command[i] = line[i];
    }
    return to_ret;
}
