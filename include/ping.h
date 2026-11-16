#ifndef PING
#define PING


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

#define ERR_MSG 1
#define WARN_MSG 2
#define NORMAL_MSG 3
#define	USAGE_ERR 4

// helper functions
void	display_messge(int fd, char *msg, int msgType);
int		valid_integer(char *str);

#endif
