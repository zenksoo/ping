#include "ping.h"
#include <asm-generic/socket.h>
#include <bits/types/struct_timeval.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>

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

uint16_t checksum_calculation(void *data, size_t length) {
	const uint16_t *buf = data;
	uint32_t sum = 0;

	printf("%s %u\n", (char *)data, *buf);

	for (; length > 1; length -= 2) {
		sum += *buf++;
	}

	// Handle odd-length packets
    if (length == 1)
        sum += *(const uint8_t *)buf;

    // Fold carry-over bits
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16); // Fold again if needed

    // Return ones' complement
    return (uint16_t)~sum;

}

void build_icmp_request(struct icmp *icmp_pkt, int seq) {
	memset(icmp_pkt, 0, sizeof(*icmp_pkt) + PAYLOAD_SIZE);

	// icmp header
	icmp_pkt->icmp_type = ICMP_ECHO;
	icmp_pkt->icmp_code = 0;
	icmp_pkt->icmp_

}

int main(int argc, char **argv) {
	struct ipaddr *res; // get ip adds as string for the target end system
	int sockfd;
	struct icmphdr *icmp;
	int	count;
	int i;
	void *buffer;

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
				return (fprintf(stderr, "ping: invalid argument: '%s'\n", argv[i]), 1);
		} else if (!find_char(argv[i], '-')) {
			res = getip(argv[i]);
			if (!res)
				return 1;
		} else if (find_char(argv[i], '-'))
			continue;
	}
	checksum_calculation("hello world", strlen("hello world"));
	return 0;
	if (!res)
		return (display_messge(2, "Destination address required", USAGE_ERR), 1);

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd == -1) {
		fprintf(stderr, "ping: socket() Failed\n");
		return (EXIT_FAILURE);
	}

	struct timeval timeout = {.tv_sec = 2, .tv_usec = 0};

	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
		fprintf(stderr, "ping: setsockopt(SO_RCVTIMEO) failed");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	icmp = (struct icmphdr *)buffer;

	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->checksum = 0;
	icmp->un.echo.id = getpid();

	for (int i = 0; *res->ipv4_buffers && i < res->ipv4_buff_size; i++)
		printf("IPV4 -> %s\n", res->ipv4_buffers[i]);


	cleanup(res);
	return 0;
}
