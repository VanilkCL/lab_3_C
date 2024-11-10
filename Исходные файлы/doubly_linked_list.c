#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include "doubly_linked_list.h"

void push_front(list* user_list, long double coefficient, long double degree)
{
	node* new_node = malloc(sizeof(node));
	while (new_node == NULL)
	{
		new_node = malloc(sizeof(node));
	}

	new_node->coefficient = coefficient;
	new_node->degree = degree;

	new_node->next = user_list->head;
	new_node->previous = NULL;

	if (user_list->size)
	{
		user_list->head->previous = new_node;
	}
	else
	{
		user_list->tail = new_node;
	}
	user_list->head = new_node;
	user_list->size++;
}

void push_back(list* user_list, long double coefficient, long double degree)
{
	node* new_node = malloc(sizeof(node));
	while (new_node == NULL)
	{
		new_node = malloc(sizeof(node));
	}

	new_node->coefficient = coefficient;
	new_node->degree = degree;

	new_node->previous = user_list->tail;
	new_node->next = NULL;

	if (user_list->size)
	{
		user_list->tail->next = new_node;
	}
	else
	{
		user_list->head = new_node;
	}
	user_list->tail = new_node;
	user_list->size++;
}

void pop_front(list* user_list)
{
	if (user_list->size == 0)
	{
		printf("IMPOSSIBLE ACTION");
		exit(1);
	}
	if (user_list->size == 1)
	{
		node* node_to_delete = user_list->head;
		user_list->head = NULL;
		user_list->tail = NULL;
		user_list->size = 0;
		free(node_to_delete);
	}
	if (user_list->size > 1)
	{
		node* node_to_delete = user_list->head;
		user_list->head = user_list->head->next;
		user_list->head->previous = NULL;
		user_list->size--;
		free(node_to_delete);
	}
}

void pop_back(list* user_list)
{
	if (user_list->size == 0)
	{
		printf("IMPOSSIBLE ACTION");
		exit(1);
	}
	if (user_list->size == 1)
	{
		node* node_to_delete = user_list->tail;
		user_list->tail = NULL;
		user_list->head = NULL;
		user_list->size = 0;
		free(node_to_delete);
	}
	if (user_list->size > 1)
	{
		node* node_to_delete = user_list->tail;
		user_list->tail = user_list->tail->previous;
		user_list->tail->next = NULL;
		user_list->size--;
		free(node_to_delete);
	}
}

void emplace(list* user_list, long double coefficient, long double degree, int index)
{
	if (index == user_list->size)
	{
		push_back(user_list, coefficient, degree);
		return;
	}
	if (index == 0)
	{
		push_front(user_list, coefficient, degree);
		return;
	}
	if (index > user_list->size)
	{
		printf("NO INDEX SUCH US!");
		exit(1);
	}
	node* curr_node = user_list->head;
	for (int i = 0; i < index; i++)
	{
		curr_node = curr_node->next;
	}

	node* new_node = malloc(sizeof(node));
	while (new_node == NULL) new_node = malloc(sizeof(node));

	new_node->coefficient = coefficient;
	new_node->degree = degree;

	new_node->next = curr_node->next;
	new_node->previous = curr_node;
	curr_node->next = new_node;
	curr_node = new_node->next;
	curr_node->previous = new_node;

	user_list->size++;
}

void erase(list* user_list, int index)
{
	if (index == user_list->size - 1)
	{
		pop_back(user_list);
		return;
	}
	if (index == 0)
	{
		pop_front(user_list);
		return;
	}
	if (index >= user_list->size)
	{
		printf("NO INDEX SUCH US!");
		exit(1);
	}
	node* node_to_delete = user_list->head, * previous, * next;
	for (int i = 0; i < index; i++)
	{
		node_to_delete = node_to_delete->next;
	}

	previous = node_to_delete->previous;
	next = node_to_delete->next;
	previous->next = next;
	next->previous = previous;
	free(node_to_delete);

	user_list->size--;
}

void clear(list* user_list)
{
	if (user_list->tail == NULL) return;
	node* current_node = user_list->tail;
	while (current_node->previous != NULL)
	{
		current_node = current_node->previous;
		free(current_node->next);
	}
	free(current_node);
	user_list->head = NULL;
	user_list->tail = NULL;
	user_list->size = 0;
}

list* create_list()
{
	list* user_list = malloc(sizeof(list));
	while (user_list == NULL) user_list = malloc(sizeof(list));
	user_list->size = 0;
	user_list->head = NULL;
	user_list->tail = NULL;
	return user_list;
}