#include "ping.h"
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <sys/socket.h>

void cleanup(struct ipaddr *res) {
	for (int i = 0; i < res->ipv4_buff_size; i++)
		free(res->ipv4_buffers[i]);

	for (int i = 0; i < res->ipv6_buff_size; i++)
		free(res->ipv6_buffers[i]);

	free(res->ipv4_buffers);
	free(res->ipv6_buffers);

	free(res);
}

int find_char(char *str, char c) {
	while (*str) {
		if (*str == c)
			return 1;
		str++;
	}
	return 0;
}

int main(int argc, char **argv) {
	struct ipaddr *res; // get ip adds as string for the target end system
	int sockfd;
	struct icmphdr *icmp;
	int	count;
	int i;

	if (argc < 2)
		return (fprintf(stderr, "ping: usage error: ping [OPTION] [DESTADDR]\n"), 1);

	res = NULL;
	count = 0;
	i = 0;
	while (++i < argc) {
		if (!strcmp(argv[i], "-V")) {
			printf("ping: noncomplate version [ 0.0.1 ]\n");
			return (0);
		} else if (!strcmp(argv[i], "-c")) {
			if (i + 1 == argc)
				return (display_messge(2, "missing argument for -c [count]", OTHER), 1);
			count = atoi(argv[++i]);
			if (!count)
				return (fprintf(stderr, "ping: invalid argument: '%s'", argv[i]), 1);
		} else if (!find_char(argv[i], '-')) {
			res = getip(argv[1]);
			if (!res)
				return 1;
		} else if (find_char(argv[i], '-'))
			continue;
	}
	if (!res)
		return (display_messge(2, "Destination address required", USAGE_ERR), 1);

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_ICMP);
	

	for (int i = 0; *res->ipv4_buffers && i < res->ipv4_buff_size; i++)
		printf("IPV4 -> %s\n", res->ipv4_buffers[i]);

	cleanup(res);
	return 0;
}
