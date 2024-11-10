#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <locale.h>
#include "doubly_linked_list.h"

void fixprecision(long double* value)
{
	*value *= 1e6;
	*value += 0.5;
	*value = floorl(*value);
	*value /= 1e6;
}

void swap(node* first_node, node* second_node)
{
	node buff_node = *first_node;
	first_node->coefficient = second_node->coefficient;
	first_node->degree = second_node->degree;
	second_node->coefficient = buff_node.coefficient;
	second_node->degree = buff_node.degree;
}

void selection_sort(list* user_list)//по убыванию
{
	node* left_node = user_list->head, * right_node = user_list->head, * best_cur_res_node = user_list->head;
	while (left_node != NULL)
	{
		best_cur_res_node = left_node;
		right_node = left_node->next;
		while (right_node != NULL)
		{
			if (right_node->degree > best_cur_res_node->degree)
			{
				best_cur_res_node = right_node;
			}
			right_node = right_node->next;
		}
		swap(left_node, best_cur_res_node);
		left_node = left_node->next;
	}
}

int special_char_user_input()
{
	char user_input = -1;
	scanf("\n%c", &user_input);
	if (user_input == '=') return 0;
	if (user_input == '+') return 1;
	printf("Данное действие не предусмотренно программой!\nПовторите ввод специального символа: ");
	return special_char_user_input();
}

long double secured_user_input(int diapason_l, int diapason_r)
{
	long double user_input;
	int was_mistake = 0;

	while (1)
	{
		if (was_mistake) printf("Это не является числом. Повторите ввод: ");
		else was_mistake = 1;
		scanf("%Lf", &user_input);
		if (getchar() == '\n') break;
		while (getchar() != '\n');
	}

	fixprecision(&user_input);
	if (diapason_r == -2) return user_input;
	if (diapason_l != -1 && (user_input < diapason_l || user_input > diapason_r))
	{
		printf("Ввод несуществующего номера.\nПовторите ввод данных: ");
		return secured_user_input(diapason_l, diapason_r);
	}

	if (diapason_l != -1 && (user_input < diapason_l || user_input > diapason_r))
	{
		return secured_user_input(diapason_l, diapason_r);
	}
	return user_input;
}

void addition_of_a_polinomial(list* user_list)
{
	selection_sort(user_list);
	node* current_node = user_list->head, * next_node;
	int index = 0;
	while (current_node != NULL)
	{
		while (current_node->next != NULL)
		{
			next_node = current_node->next;
			if (next_node->degree == current_node->degree)
			{
				current_node->coefficient += next_node->coefficient;
				fixprecision(&current_node->coefficient);
				erase(user_list, index + 1);
			}
			else break;
		}
		current_node = current_node->next;
		index++;
	}
}

void input_polynomial(list* user_list)
{
	char is_next_iteration = 0;
	long double coefficient, degree;
	printf("\nВведите составляющие многочлена:\n");
	do
	{
		printf("\nВведите коэффициент аргумента: ");
		coefficient = secured_user_input(-1, -1);

		printf("Введите степень аргумента: ");
		degree = secured_user_input(-1, -1);
		if (coefficient != 0) push_back(user_list, coefficient, degree);
		printf("\nДля добавления нового члена введите '+' (без кавычек).\n");
		printf("Чтобы закончиить ввод многочлена введите '=' (без кавычек): ");
		is_next_iteration = special_char_user_input();
	} while (is_next_iteration);
	addition_of_a_polinomial(user_list);
	printf("\nВвод многочлена завершён.");
}

void computation_of_a_polynomial(list* user_list)
{
	printf("\nВведите значение аргумента: ");
	long double x = secured_user_input(-1, -2);
	node* cur_node = user_list->head;
	long double ans = 0, degree_result;
	while (cur_node != NULL && x != 0)
	{
		if (cur_node->degree < 0) degree_result = powl(x, cur_node->degree);
		else degree_result = powl(x, cur_node->degree);
		fixprecision(&degree_result);
		ans += cur_node->coefficient * degree_result;
		fixprecision(&ans);
		cur_node = cur_node->next;
	}
	printf("\nЗначение многочлена при заданном аргументе равно %Lf\n", ans);
}

void print_polynomial_action_result(list* result_list)
{
	addition_of_a_polinomial(result_list);
	node* cur_node = result_list->head;
	if (!result_list->size)
	{
		printf("%d\n", 0);
		return;
	}
	if (cur_node->coefficient != 0) printf("%Lf*x^%Lf", cur_node->coefficient, cur_node->degree);
	cur_node = cur_node->next;
	while (cur_node != NULL)
	{
		if (cur_node->coefficient > 0)
		{
			printf("+%Lf*x^%Lf", cur_node->coefficient, cur_node->degree);
		}
		else if (cur_node->coefficient < 0)
		{
			printf("%Lf*x^%Lf", cur_node->coefficient, cur_node->degree);
		}
		if (cur_node->next == NULL) break;
		cur_node = cur_node->next;
	}
	printf("\n");
}

void sum_of_polynomial(list* first_polynomial, list* second_polynomial)
{
	list* result = create_list();
	node* cur_node_first_polynomial = first_polynomial->head,
		* cur_node_second_polynomial = second_polynomial->head;
	while (cur_node_first_polynomial != NULL || cur_node_second_polynomial != NULL)
	{
		if (cur_node_first_polynomial == NULL)
		{
			while (cur_node_second_polynomial != NULL)
			{
				push_back(result, cur_node_second_polynomial->coefficient,
					cur_node_second_polynomial->degree);
				cur_node_second_polynomial = cur_node_second_polynomial->next;
			}
			break;
		}
		if (cur_node_second_polynomial == NULL)
		{
			while (cur_node_first_polynomial != NULL)
			{
				push_back(result, cur_node_first_polynomial->coefficient,
					cur_node_first_polynomial->degree);
				cur_node_first_polynomial = cur_node_first_polynomial->next;
			}
			break;
		}
		if (cur_node_first_polynomial->degree == cur_node_second_polynomial->degree)
		{
			push_back(result, cur_node_first_polynomial->coefficient +
				cur_node_second_polynomial->coefficient, cur_node_first_polynomial->degree);
			cur_node_first_polynomial = cur_node_first_polynomial->next;
			cur_node_second_polynomial = cur_node_second_polynomial->next;
			continue;
		}
		if (cur_node_first_polynomial->degree > cur_node_second_polynomial->degree)
		{
			push_back(result, cur_node_first_polynomial->coefficient,
				cur_node_first_polynomial->degree);
			cur_node_first_polynomial = cur_node_first_polynomial->next;
			continue;
		}
		if (cur_node_first_polynomial->degree < cur_node_second_polynomial->degree)
		{
			push_back(result, cur_node_second_polynomial->coefficient,
				cur_node_second_polynomial->degree);
			cur_node_second_polynomial = cur_node_second_polynomial->next;
			continue;
		}
	}
	printf("Сумма многочленов равна:\n");
	print_polynomial_action_result(result);
	clear(result);
	free(result);
}

void dif_of_polynomial(list* first_polynomial, list* second_polynomial)
{
	list* result = create_list();
	node* cur_node_first_polynomial = first_polynomial->head,
		* cur_node_second_polynomial = second_polynomial->head;
	while (cur_node_first_polynomial != NULL || cur_node_second_polynomial != NULL)
	{
		if (cur_node_first_polynomial == NULL)
		{
			while (cur_node_second_polynomial != NULL)
			{
				push_back(result, -cur_node_second_polynomial->coefficient,
					cur_node_second_polynomial->degree);
				cur_node_second_polynomial = cur_node_second_polynomial->next;
			}
			break;
		}
		if (cur_node_second_polynomial == NULL)
		{
			while (cur_node_first_polynomial != NULL)
			{
				push_back(result, cur_node_first_polynomial->coefficient,
					cur_node_first_polynomial->degree);
				cur_node_first_polynomial = cur_node_first_polynomial->next;
			}
			break;
		}
		if (cur_node_first_polynomial->degree == cur_node_second_polynomial->degree)
		{
			push_back(result, cur_node_first_polynomial->coefficient -
				cur_node_second_polynomial->coefficient, cur_node_first_polynomial->degree);
			cur_node_first_polynomial = cur_node_first_polynomial->next;
			cur_node_second_polynomial = cur_node_second_polynomial->next;
			continue;
		}
		if (cur_node_first_polynomial->degree > cur_node_second_polynomial->degree)
		{
			push_back(result, cur_node_first_polynomial->coefficient,
				cur_node_first_polynomial->degree);
			cur_node_first_polynomial = cur_node_first_polynomial->next;
			continue;
		}
		if (cur_node_first_polynomial->degree < cur_node_second_polynomial->degree)
		{
			push_back(result, -cur_node_second_polynomial->coefficient,
				cur_node_second_polynomial->degree);
			cur_node_second_polynomial = cur_node_second_polynomial->next;
			continue;
		}
	}
	printf("Разность многочленов равна:\n");
	print_polynomial_action_result(result);
	clear(result);
	free(result);
}

void product_of_polynomial(list* first_polynomial, list* second_polynomial)
{
	list* result = create_list();
	node* node_in_first_polynomial = first_polynomial->head, * node_in_second_polynomial;
	long double to_coefficint_push_back, to_degree_push_back;
	while (node_in_first_polynomial != NULL)
	{
		node_in_second_polynomial = second_polynomial->head;
		while (node_in_second_polynomial != NULL)
		{
			to_coefficint_push_back = node_in_first_polynomial->coefficient * node_in_second_polynomial->coefficient;
			fixprecision(&to_coefficint_push_back);
			to_degree_push_back = node_in_first_polynomial->degree + node_in_second_polynomial->degree;
			fixprecision(&to_degree_push_back);
			push_back(result, to_coefficint_push_back, to_degree_push_back);
			node_in_second_polynomial = node_in_second_polynomial->next;
		}
		node_in_first_polynomial = node_in_first_polynomial->next;
	}
	printf("Произведение многочленов равно:\n");
	print_polynomial_action_result(result);
	clear(result);
	free(result);
}

void division_of_polynomial(list* first_polynomial, list* second_polynomial)
{
	list* complete_division = create_list(), * l_remainder = create_list();
	node* node_in_first_polynomial = first_polynomial->head,
		* node_in_second_polynomial = second_polynomial->head,
		* node_in_l_remainder;
	long double diff_degree, diff_coefficient, curr_degree, curr_coefficient;
	for (int i = 0; i < first_polynomial->size; i++)
	{
		if (i)
		{
			while (l_remainder->tail->degree - 1 != node_in_first_polynomial->degree)
			{
				push_back(remainder, 0, l_remainder->tail->degree);
			}
		}
		push_back(l_remainder, node_in_first_polynomial->coefficient,
			node_in_first_polynomial->degree);
		node_in_first_polynomial = node_in_first_polynomial->next;
	}
	while (1)
	{
		while (l_remainder->size && l_remainder->head->coefficient == 0)
		{
			pop_front(l_remainder);
		}
		if (!l_remainder->size) break;
		diff_degree = l_remainder->head->degree - second_polynomial->head->degree;
		if (diff_degree < 0) break;
		diff_coefficient = l_remainder->head->coefficient / second_polynomial->head->coefficient;
		fixprecision(&diff_degree);
		fixprecision(&diff_coefficient);
		push_back(complete_division, diff_coefficient, diff_degree);
		node_in_l_remainder = l_remainder->head;
		node_in_second_polynomial = second_polynomial->head;
		while (node_in_l_remainder != NULL)
		{
			curr_degree = node_in_second_polynomial->degree +
				complete_division->head->degree;
			fixprecision(&curr_degree);
			if (node_in_l_remainder->degree != curr_degree)
			{
				node_in_l_remainder = node_in_l_remainder->next;
			}
			else
			{
				node_in_l_remainder->coefficient -= node_in_second_polynomial->coefficient
					* complete_division->head->coefficient;
				fixprecision(&node_in_l_remainder->coefficient);
				if (node_in_second_polynomial->next == NULL) break;
				node_in_second_polynomial = node_in_second_polynomial->next;
				node_in_l_remainder = node_in_l_remainder->next;
			}
		}
	}
	printf("Частное многочленов равно:\n");
	print_polynomial_action_result(complete_division);
	printf("Остаток от деления многочленов равен:\n");
	print_polynomial_action_result(l_remainder);
	clear(complete_division);
	free(complete_division);
	clear(l_remainder);
	free(l_remainder);
}

void next_action(list* first_polynomial, list* second_polynomial)
{
	int numerable = 1, max_num_to_inp, current_action;

	if (first_polynomial->head != NULL && second_polynomial == NULL) max_num_to_inp = 5;
	if (first_polynomial->head == NULL && second_polynomial != NULL) max_num_to_inp = 5;
	if (first_polynomial->head == NULL && second_polynomial == NULL) max_num_to_inp = 3;
	if (first_polynomial->head != NULL && second_polynomial != NULL) max_num_to_inp = 11;

	int* match = malloc(sizeof(int) * max_num_to_inp);
	while (match == NULL) match = malloc(sizeof(int) * max_num_to_inp);

	printf("\nВыберите действие программы из предложенного списка введя с клавиатуры число от 1 до %d.\n", max_num_to_inp);
	if (first_polynomial->head == NULL)
	{
		match[numerable - 1] = 1;
		printf("%d] Ввести первый многочлен\n", numerable++);
	}
	else
	{
		match[numerable - 1] = 2;
		printf("%d] Перезаписать первый многочлен\n", numerable++);
	}
	if (second_polynomial->head == NULL)
	{
		match[numerable - 1] = 3;
		printf("%d] Ввести второй многочлен\n", numerable++);
	}
	else
	{
		match[numerable - 1] = 4;
		printf("%d] Перезаписать второй многочлен\n", numerable++);
	}
	if (first_polynomial->head != NULL)
	{
		match[numerable - 1] = 5;
		printf("%d] Вычислить значение первого многочлена\n", numerable++);
	}
	if (second_polynomial->head != NULL)
	{
		match[numerable - 1] = 6;
		printf("%d] Вычислить значение второго многочлена\n", numerable++);
	}
	if (first_polynomial->head != NULL)
	{
		match[numerable - 1] = 7;
		printf("%d] Удалить первый многочлен\n", numerable++);
	}
	if (second_polynomial->head != NULL)
	{
		match[numerable - 1] = 8;
		printf("%d] Удалить второй многочлен\n", numerable++);
	}
	if (first_polynomial->head != NULL && second_polynomial->head != NULL)
	{
		match[numerable - 1] = 9;
		printf("%d] Вычислить сумму многочленов\n", numerable++);
		match[numerable - 1] = 10;
		printf("%d] Вычислить разность многочленов\n", numerable++);
		match[numerable - 1] = 11;
		printf("%d] Вычислить произведение многочленов\n", numerable++);
		match[numerable - 1] = 12;
		printf("%d] Вычислить частное многочленов\n", numerable++);
	}
	match[numerable - 1] = 13;
	printf("%d] Завершение работы программы\n", numerable++);
	current_action = match[(int)secured_user_input(1, max_num_to_inp) - 1];
	free(match);
	switch (current_action)
	{
	case 1:
		input_polynomial(first_polynomial);
		break;
	case 2:
		clear(first_polynomial);
		input_polynomial(first_polynomial);
		break;
	case 3:
		input_polynomial(second_polynomial);
		break;
	case 4:
		clear(second_polynomial);
		input_polynomial(second_polynomial);
		break;
	case 5:
		computation_of_a_polynomial(first_polynomial);
		break;
	case 6:
		computation_of_a_polynomial(second_polynomial);
		break;
	case 7:
		clear(first_polynomial);
		break;
	case 8:
		clear(second_polynomial);
		break;
	case 9:
		sum_of_polynomial(first_polynomial, second_polynomial);
		break;
	case 10:
		dif_of_polynomial(first_polynomial, second_polynomial);
		break;
	case 11:
		product_of_polynomial(first_polynomial, second_polynomial);
		break;
	case 12:
		division_of_polynomial(first_polynomial, second_polynomial);
		break;
	case 13:
		return;
	}
	next_action(first_polynomial, second_polynomial);
}

int main()
{
	setlocale(0, "");
	list* first_polynomial = create_list(), * second_polynomial = create_list();
	printf("Для начала пользовония программой введите первый многочлен.\n");
	input_polynomial(first_polynomial);

	next_action(first_polynomial, second_polynomial);

	clear(first_polynomial);
	free(first_polynomial);
	clear(second_polynomial);
	free(second_polynomial);
	printf("zzz..");
}