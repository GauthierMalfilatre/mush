/*
** EPITECH PROJECT, 2025
** MINISHELL2
** File description:
** Tokenize an AST
*/
#include <string.h>
#include "my.h"
#include "mysh.h"

const token_map_t token_map[] = {
    {"|", AST_PIPE},
    {";", AST_SEMICOLON},
    {"<", AST_REDIRECT_IN},
    {">", AST_REDIRECT_OUT},
    {"<<", AST_REDIRECT_ININ},
    {">>", AST_REDIRECT_OUTOUT},
    {0, 0},
};

int get_token_type(const token_map_t *token_map, char *token)
{
    for (int i = 0; token_map[i].token; i++) {
        if (!my_strcmp(token, token_map[i].token)) {
            return token_map[i].type;
        }
    }
    return AST_COMMAND;
}
