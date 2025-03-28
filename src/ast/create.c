/*
** EPITECH PROJECT, 2025
** MINISHELL2
** File description:
** Create an AST
*/
#include <string.h>
#include "my.h"
#include "mysh.h"

ast_node_t *create_ast_node(ast_e_t type, char *value)
{
    ast_node_t *node = malloc(sizeof(ast_node_t));

    if (!node) {
        my_printf("Failed to create AST node\n");
        return NULL;
    }
    node->type = type;
    node->value = value ? my_strdup(value) : NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void destroy_ast_node(ast_node_t *node)
{
    if (node) {
        if (node->value) {
            free(node->value);
        }
        free(node);
    }
}

void destroy_ast(ast_node_t *root)
{
    if (root) {
        destroy_ast(root->left);
        destroy_ast(root->right);
        destroy_ast_node(root);
    }
}
