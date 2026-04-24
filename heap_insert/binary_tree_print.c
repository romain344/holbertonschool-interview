#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "binary_trees.h"

/* Forward declaration */
static void _binary_tree_print_helper(const binary_tree_t *tree, int offset,
									  int depth, char **s);
static int _binary_tree_height(const binary_tree_t *tree);

/**
 * _binary_tree_height - Measures the height of a binary tree
 * @tree: Pointer to the root node of the tree
 *
 * Return: The height of the tree
 */
static int _binary_tree_height(const binary_tree_t *tree)
{
	int height_l = 0;
	int height_r = 0;

	if (!tree)
		return (0);

	if (tree->left)
		height_l = 1 + _binary_tree_height(tree->left);
	if (tree->right)
		height_r = 1 + _binary_tree_height(tree->right);

	return (height_l > height_r ? height_l : height_r);
}

/**
 * _binary_tree_print_helper - Prints a binary tree
 * @tree: Pointer to the root node of the tree
 * @offset: Offset to print at
 * @depth: Depth of the current node
 * @s: String in which the line will be printed
 */
static void _binary_tree_print_helper(const binary_tree_t *tree, int offset,
									  int depth, char **s)
{
	char b[6];
	int width;
	int i;

	if (!tree)
		return;

	width = sprintf(b, "(%03d)", tree->n);

	_binary_tree_print_helper(tree->left, offset - pow(2, depth - 1), depth - 1,
							  s);

	for (i = 0; i < width; i++)
		s[depth][offset + i] = b[i];

	_binary_tree_print_helper(tree->right, offset + pow(2, depth - 1), depth - 1,
							  s);
}

/**
 * binary_tree_print - Prints a binary tree
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char **s;
	size_t height;
	int i;
	int j;

	if (!tree)
		return;

	height = _binary_tree_height(tree);
	s = malloc(sizeof(*s) * (height + 1));
	if (!s)
		return;

	for (i = 0; i <= (int)height; i++)
	{
		s[i] = malloc(sizeof(**s) * 255);
		if (!s[i])
			return;
		memset(s[i], 32, 254);
		s[i][254] = '\0';
	}
	_binary_tree_print_helper(tree, 0, height, s);
	for (i = 0; i <= (int)height; i++)
	{
		for (j = 254 - 1; j >= 0; j--)
		{
			if (s[i][j] != 32)
				break;
		}
		printf("%s\n", s[i]);
		free(s[i]);
	}
	free(s);
}
