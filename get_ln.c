#include "main.h"

/**
 * bring_line - assign the line variable for get_line
 * @lineptr: Buffer that store the inputs string
 * @buffer: the string that is been called to line
 * @n:the size of line
 * @j: the size of buffer
 */
void bring_line(char **lineptr, size_t *f, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*f = j;

		else
			*f = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*f < j)
	{
		if (j > BUFSIZE)
			*f = j;
		else
			*f = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpts from the stream
 * @lineptr: buffer that stores the input
 * @n: the size of lineptr
 * @stream:the stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int s;
	static ssize_t inputs;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (inputs == 0)
		fflush(stream);
	else
		return (-1);
	inputs = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		s = read(STDIN_FILENO, &t, 1);
		if (s == -1 || (s == 0 && inputs == 0))
		{
			free(buffer);
			return (-1);
		}
		if (s == 0 && inputs != 0)
		{
			inputs++;
			break;
		}
		if (inputs >= BUFSIZE)
			buffer = _realloc(buffer, inputs, inputs + 1);
		buffer[inputs] = t;
		inputs++;
	}
	buffer[inputs] = '\0';
	bring_line(lineptr, n, buffer, inputs);
	retval = inputs;
	if (s != 0)
		inputs = 0;
	return (retval);
}
