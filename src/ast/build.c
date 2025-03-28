/*
** EPITECH PROJECT, 2025
** MINISHELL2
** File description:
** Build an AST in a nutshell
*/
#include <string.h>
#include "my.h"
#include "mysh.h"

ast_node_t *handle_command(ast_node_t *current_command, char *token)
{
    ast_node_t *command_part = 0;

    if (!current_command) {
        current_command = create_ast_node(AST_COMMAND, token);
    } else {
        command_part = create_ast_node(AST_COMMAND, token);
        current_command->right = command_part;
        current_command = command_part;
    }
    return current_command;
}

ast_node_t *handle_operator(ast_node_t *last_operator,
    ast_node_t *current_command, ast_e_t type, char *token)
{
    ast_node_t *operator_node = create_ast_node(type, token);

    if (last_operator) {
        last_operator->right = operator_node;
    } else if (current_command) {
        current_command->right = operator_node;
    }
    return operator_node;
}

ast_node_t *build_ast(const token_map_t *token_map, char **tokens)
{
    ast_node_t *root = NULL;
    ast_node_t *current_command = NULL;
    ast_node_t *last_operator = NULL;
    ast_e_t type = 0;
    char *token = NULL;

    for (int i = 0; tokens[i]; i++) {
        token = tokens[i];
        type = get_token_type(token_map, token);
        if (type == AST_COMMAND) {
            current_command = handle_command(current_command, token);
        } else {
            last_operator = handle_operator(last_operator, current_command,
                type, token);
            current_command = NULL;
        }
    }
    return root;
}
