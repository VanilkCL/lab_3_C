#pragma once

typedef struct
{
	long double coefficient;
	long double degree;
	struct node* next;
	struct node* previous;
} node;

typedef struct
{
	node* head;
	node* tail;
	int size;
} list;

void push_front(list* user_list, long double coefficient, long double degree);
void push_back(list* user_list, long double coefficient, long double degree);
void pop_front(list* user_list);
void pop_back(list* user_list);
void emplace(list* user_list, long double coefficient, long double degree, int index);
void erase(list* user_list, int index);
void clear(list* user_list);
list* create_list();