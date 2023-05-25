#include "main.h"

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_len(int n)
{
	unsigned int n1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}
/**
 * aux_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *aux_itoa(int n)
{
	unsigned int n1;
	int lenght = get_len(n);
	char *buff;

	buff = malloc(sizeof(char) * (lenght + 1));
	if (buff == 0)
		return (NULL);

	*(buff + lenght) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buff[0] = '-';
	}
	else
	{
		n1 = n;
	}

	lenght--;
	do {
		*(buff + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}
	while (n1 > 0)
		;
	return (buff);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int temp = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + temp) != '\0')
	{
		if (size > 0 && (*(s + temp) < '0' || *(s + temp) > '9'))
			break;

		if (*(s + temp) == '-')
			pn *= -1;

		if ((*(s + temp) >= '0') && (*(s + temp) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		temp++;
	}

	for (i = temp - size; i < temp; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
