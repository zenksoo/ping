#include "ping.h"

void	display_error()
{
	char *err_msg = "\033[31mERROR\033[39m: Invalid Argument\n";
	write(2, err_msg, strlen(err_msg));
}

int		valid_integer(char *st)
{
	
	return (1);
}


