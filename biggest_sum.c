#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define CYAN	"\x1B[36m"
#define RESET	"\x1B[0m"

/**
 * _atoi - Converts a string to a number
 *
 * @n: Pointer to the location to store the converted int
 * @s: Pointer to the string to convert
 *
 * Return: 1 on success, 0 on error
 */
int _atoi(int *n, const char *s)
{
	size_t i;

	i = 0;
	if (s[0] == '-' || s[0] == '+')
		i = 1;
	for (; s && s[i]; ++i)
		if (s[i] < '0' || s[i] > '9')
		{
			fprintf(stderr, "%s is not a digit\n", s);
			return (0);
		}
	*n = atoi(s);
	return (1);
}

/**
 * init_array - Initializes the array
 *
 * @size: Size of the array
 * @av: Array of strings to convert
 *
 * Return: The initialized array, or NULL on failure
 */
int *init_array(size_t size, const char **av)
{
	int *array;
	size_t i;

	array = malloc(sizeof(*array) * size);
	if (!array)
	{
		fprintf(stderr, "Failed to malloc\n");
		return (NULL);
	}
	for (i = 0; i < size; ++i)
	{
		if (!(_atoi(&(array[i]), av[i])))
		{
			free(array);
			return (NULL);
		}
	}
	return (array);
}

/**
 * biggest_sum - Finds the biggest sum in an array
 *
 * @array: Pointer to the array of integers
 * @size: Size of the array
 * @start: Pointer to the int to store the first index of the biggest sum
 *
 * Return: The biggest sum
 */
int biggest_sum(int *array, size_t size, size_t *start)
{
	size_t i;
	int max_so_far;
	int max_ending_here;

	max_so_far = INT_MIN;
	max_ending_here = 0;
	for (i = 0; i < size; ++i)
	{
		if (max_ending_here == 0)
			*start = i;
		max_ending_here = max_ending_here + array[i];
		if (max_so_far < max_ending_here)
			max_so_far = max_ending_here;
		if (max_ending_here < 0)
			max_ending_here = 0;
	}
	return (max_so_far);
}

/**
 * print_array - Prints out an array of integers
 *
 * @array: Pointer to the array to be printed
 * @size: Size of the array
 * @biggest: Biggest sum
 * @idx: Index of the biggest sum
 */
void print_array(const int *array, size_t size, int biggest, size_t idx)
{
	size_t i;
	int sum, passed;

	for (passed = 0, sum = 0, i = 0; i < size; ++i)
	{
		if (i)
			printf(", ");
		if (i >= idx)
		{
			sum += array[i];
			if (!passed)
				printf(CYAN);
			if (sum == biggest)
				passed = 1;
		}
		printf("%d", array[i]);
		printf(RESET);
	}
	printf("\n");
}

/**
 * main - Entry point
 *
 * @ac: Arguments counter
 * @av: Arguments vector
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int ac, const char **av)
{
	int *array;
	size_t size, i;
	int biggest;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s <n0> [n1]...\n", av[0]);
		return (EXIT_FAILURE);
	}
	size = ac - 1;
	array = init_array(size, av + 1);
	if (!array)
		return (EXIT_FAILURE);
	biggest = biggest_sum(array, size, &i);
	print_array(array, size, biggest, i);
	printf("Biggest sum: %d\n", biggest);
	free(array);
	return (EXIT_SUCCESS);
}
