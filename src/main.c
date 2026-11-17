#include "ping.h"

void cleanup(struct ipaddr *res) {
	for (int i = 0; i < res->ipv4_buff_size; i++)
		free(res->ipv4_buffers[i]);

	for (int i = 0; i < res->ipv6_buff_size; i++)
		free(res->ipv6_buffers[i]);

	free(res->ipv4_buffers);
	free(res->ipv6_buffers);

	free(res);
}

int main(int argc, char **argv) {
	int	count;
	int	opt;
	int i;
	char buffer[INET6_ADDRSTRLEN];
	struct ipaddr *res; // get ip adds as string for the target end system

	if (argc < 2)
		return (fprintf(stderr, "ping: Usage: ping [OPTION] [DEST...]\n"), 1);

	res = getip(argv[1]);
	if (!res)
		return 1;

	printf("%d -- %d\n", res->ipv4_buff_size, res->ipv6_buff_size);

	for (int i = 0; i < res->ipv4_buff_size; i++)
		printf("IPV4 -> %s\n", res->ipv4_buffers[i]);

	for (int i = 0; i < res->ipv6_buff_size; i++)
		printf("IPV6 -> %s\n", res->ipv6_buffers[i]);
	cleanup(res);
	return 0;
}
