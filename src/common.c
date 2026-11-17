#include "ping.h"

void display_messge(int fd, char *msg, int msgType)
{
	char *msg_type;

	if (msgType == USAGE_ERR)
		msg_type = "ping: usage error: ";
	else if(msgType == UNKOWN_HOST)
		msg_type = "ping: ";
	// else if (msgType == ERR_MSG)
	// 	msg_type = "\033[31mERROR\033[39m: ";
	// else if (msgType == WARN_MSG)
	// 	msg_type = "\033[33mWARNING\033[39m: ";
	else if (msgType == OTHER)
		msg_type = "ping: ";


	write(fd, msg_type, strlen(msg_type));
	write(fd, msg, strlen(msg));

	if (msg[strlen(msg) - 1] != '\n')
		write(fd, "\n", 1);
}

int	valid_integer(char *st)
{
	return (1);
}


