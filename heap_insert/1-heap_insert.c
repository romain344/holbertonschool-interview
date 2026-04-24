#include "binary_trees.h"

/**
 * tree_size - Counts the nodes in a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Number of nodes
 */
static size_t tree_size(const binary_tree_t *tree)
{
    if (!tree)
        return (0);
    return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * get_insert_parent - Finds the parent node where the next node should
 *                     be inserted to keep the heap a complete binary tree
 * @root: Pointer to the root node
 * @size: Current size of the heap (number of nodes)
 *
 * Return: Pointer to the parent node for insertion
 */
static heap_t *get_insert_parent(heap_t *root, size_t size)
{
    size_t path;
    size_t levels;
    size_t bit;

    /* Position of the new node (1-indexed): size + 1 */
    /* Navigate from root using binary representation of position */
    /* e.g. size+1 = 5 -> binary 101 -> go left then right from root */

    path = size + 1;
    levels = 0;
    bit = path;

    /* Find the number of bits */
    while (bit > 1)
    {
        levels++;
        bit >>= 1;
    }

    /* Follow bits from second-most significant to least significant */
    bit = 1 << (levels - 1);
    while (bit > 1)
    {
        bit >>= 1;
        if (bit == 1)
            break;
        if (path & bit)
            root = root->right;
        else
            root = root->left;
    }

    return (root);
}

/**
 * heap_insert - Inserts a value in a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 * @value: Value to insert
 *
 * Return: Pointer to the inserted node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *parent;
    heap_t *node;
    size_t size;
    int tmp;

    if (!root)
        return (NULL);

    if (!*root)
    {
        *root = binary_tree_node(NULL, value);
        return (*root);
    }

    size = tree_size(*root);
    parent = get_insert_parent(*root, size);

    /* Insert as left or right child */
    if (!parent->left)
        node = binary_tree_node(parent, value);
    else
        node = binary_tree_node(parent, value);

    if (!parent->left)
        parent->left = node;
    else
        parent->right = node;

    if (!node)
        return (NULL);

    /* Bubble up: swap values until Max Heap property is restored */
    while (node->parent && node->n > node->parent->n)
    {
        tmp = node->n;
        node->n = node->parent->n;
        node->parent->n = tmp;
        node = node->parent;
    }

    return (node);
}