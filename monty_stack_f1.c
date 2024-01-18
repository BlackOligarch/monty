#include "monty.h"


/**
 * add_to_stack - It adds a node to the stack.
 * @new_node: The pointer to the new node.
 * @ln: The integer representing the line number of of the opcode.
 */
void add_2_stack(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	head = *new_node;
	head->next = tmp;
	tmp->prev = head;
}


/**
 * print_stack - It adds a node to the stack.
 * @stack: The pointer to a pointer pointing to top node of the stack.
 * @line_num: The line number of  the opcode.
 */
void print_stack(stack_t **stack, unsigned int line_num)
{
	stack_t *tmp;

	(void) line_num;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * pop_top - It adds a node to the stack.
 * @stack: The pointer to a pointer pointing to top node of the stack.
 * @line_num: The integer representing the line num of of the opcode.
 */
void pop_top(stack_t **stack, unsigned int line_num)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
		more_err(7, line_num);

	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * print_top - It prints the top node of the stack.
 * @stack: The pointer to a pointer pointing to top node of the stack.
 * @line_num: The integer representing the line num of of the opcode.
 */
void print_top(stack_t **stack, unsigned int line_num)
{
	if (stack == NULL || *stack == NULL)
		more_err(6, line_num);
	printf("%d\n", (*stack)->n);
}
