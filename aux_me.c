#include "main.h"

/**
 * _memcpy - The copies info btw void pointers.
 * @newptr:The destination pointer.
 * @ptr:The source pointer.
 * @size:The size of the new pointer.
 *
 * Return: no return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_pointerr = (char *)ptr;
	char *char_nwptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_nwptr[i] = char_pointer[i];
}

/**
 * _realloc - The reallocates a memory block.
 * @ptr: The pointer to the memory previously allocated.
 * @old_size:The size, in bytes, of the allocated space of ptr.
 * @new_size: The new size, in bytes, of the new memory block.
 *
 * Return: pointer.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newpt;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newpt = malloc(new_size);
	if (newpt == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newpt, ptr, new_size);
	else
		_memcpy(newpt, ptr, old_size);

	free(ptr);
	return (newpt);
}

/**
 * _reallocdp -The reallocates a memory block of a double pointer.
 * @ptr: The double pointer to the memory previously allocated.
 * @old_size:The size, in bytes, of the allocated space of ptr.
 * @new_size: The new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newpt;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newpt = malloc(sizeof(char *) * new_size);
	if (newpt == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newpt[i] = ptr[i];

	free(ptr);

	return (newpt);
}
