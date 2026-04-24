#include "binary_trees.h"

/**
 * bfs_insert - Inserts new_node at next available position using BFS
 * @root: Root of the heap
 * @new_node: Node to insert
 */
static void bfs_insert(heap_t *root, heap_t *new_node)
{
	heap_t *queue[1024];
	heap_t *parent;
	int front, rear;

	front = 0;
	rear = 0;
	queue[rear++] = root;
	while (front < rear)
	{
		parent = queue[front++];
		if (!parent->left)
		{
			parent->left = new_node;
			new_node->parent = parent;
			return;
		}
		queue[rear++] = parent->left;
		if (!parent->right)
		{
			parent->right = new_node;
			new_node->parent = parent;
			return;
		}
		queue[rear++] = parent->right;
	}
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
	heap_t *new_node;
	int tmp;

	if (!root)
		return (NULL);

	new_node = binary_tree_node(NULL, value);
	if (!new_node)
		return (NULL);

	if (!*root)
	{
		*root = new_node;
		return (new_node);
	}

	bfs_insert(*root, new_node);

	while (new_node->parent && new_node->n > new_node->parent->n)
	{
		tmp = new_node->n;
		new_node->n = new_node->parent->n;
		new_node->parent->n = tmp;
		new_node = new_node->parent;
	}

	return (new_node);
}
