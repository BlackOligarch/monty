#include "monty.h"

/**
 * open_file - it opens a file
 * @file_name: the file namepath
 * Return: void
 */

void open_file(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		err(2, file_name);

	read_file(fd);
	fclose(fd);
}


/**
 * read_file - it reads a file
 * @fd: pointer to file descriptor
 * Return: void
 */

void read_file(FILE *fd)
{
	int line_num, fmt = 0;
	char *buffer = NULL;
	size_t len = 0;

	for (line_num = 1; getline(&buffer, &len, fd) != -1; line_num++)
	{
		fmt = parse_line(buffer, line_num, fmt);
	}
	free(buffer);
}


/**
 * parse_line - Separates each line into tokens to determine
 * which function to call
 * @buffer: line from the file
 * @line_num: line number
 * @fmt:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */

int parse_line(char *buffer, int line_num, int fmt)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		err(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (fmt);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	search_func(opcode, value, line_num, fmt);
	return (fmt);
}

/**
 * search_func - searches the appropriate function for the opcode
 * @opcode: the opcode
 * @value: the argument of opcode
 * @fmt: the storage format. If 0 Nodes will be entered as a stack.
 * @ln: the line number
 * if 1 nodes will be entered as a queue.
 * Return: void
 */
void search_func(char *opcode, char *value, int ln, int fmt)
{
	int i, flag;

	instruction_t func_list[] = {
		{"push", add_to_stack},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_char},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_fun(func_list[i].f, opcode, value, ln, fmt);
			flag = 0;
		}
	}
	if (flag == 1)
		err(3, ln, opcode);
}


/**
 * call_fun - calls the required function.
 * @func: pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @fmt: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void call_fun(op_func func, char *op, char *val, int ln, int fmt)
{
	stack_t *node;
	int flag = 1;
	int i = 0;

	switch (strcmp(op, "push"))
	{
		case 0:
			if (val != NULL && val[0] == '-')
			{
				val += 1;
				flag = -1;
			}
			if (val == NULL)
				err(5, ln);
			for (i = 0; val[i] != '\0'; i++)
			{
			if (!isdigit(val[i]))
				err(5, ln);
			}

				node = create_node(atoi(val) * flag);
				/* used a switch case */
				switch (fmt)
				{
				case 0:
				func(&node, ln);
				break;
				case 1:
				add_to_queue(&node, ln);
				break;
				}
				break;
				default:
				func(&head, ln);
				}
	}
