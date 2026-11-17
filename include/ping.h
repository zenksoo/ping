#ifndef PING
#define PING


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define OTHER 0
#define ERR_MSG 1
#define WARN_MSG 2
#define NORMAL_MSG 3
#define	USAGE_ERR 4
#define UNKOWN_HOST 5

struct ipaddr {
	// list of ips as string
	char	**ipv4_buffers;
	char	**ipv6_buffers;
	int		ipv4_buff_size;
	int		ipv6_buff_size;
};

struct ipaddr *getip(char *);

// helper functions
void	display_messge(int fd, char *msg, int msgType);
int		valid_integer(char *str);

#endif
