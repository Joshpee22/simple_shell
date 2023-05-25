#include "main.h"

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int temp = 0, k, l;
	char *str, mal;

	while (temp >= 0)
	{
		if (s[temp] == '\0')
			break;
		temp++;
	}
	str = s;

	for (k = 0; k < (temp - 1); k++)
	{
		for (l = k + 1; l > 0; l--)
		{
			mal = *(str + l);
			*(str + l) = *(str + (l - 1));
			*(str + (l - 1)) = mal;
		}
	}
}
