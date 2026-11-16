#include "ping.h"

void display_messge(int fd, char *msg, int msgType)
{
	char *msg_type;

	if (msgType == USAGE_ERR)
		msg_type = "ping: usage error: ";
	else if (msgType == ERR_MSG)
		msg_type = "\033[31mERROR\033[39m: ";
	else if (msgType == WARN_MSG)
		msg_type = "\033[33mWARNING\033[39m: ";
	else
		msg_type = "";


	write(2, msg_type, strlen(msg_type));
	write(2, msg, strlen(msg));

	if (msg[strlen(msg) - 1] != '\n')
		write(fd, "\n", 1);
}

int	valid_integer(char *st)
{
	return (1);
}


