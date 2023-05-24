#include "main.h"

/**
 * get_sigint - Handle the crtl + c cals in prmpt
 * @sig: the Signal handler
 */
void get_sigint(int sig_nal)
{
	(void)sig_nal;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
