#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>

int32_t get_domain_ip_addr(char *domain_name)
{
	int				status;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo *tmp_r;
	int				buff_idx;
	char **buffer;
	// char buffer[INET6_ADDRSTRLEN];
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	status = getaddrinfo(domain_name, 0, &hints, &res);
	
	printf("IP addresses for %s: \n", domain_name);

	tmp_r = res;

	buffer = malloc(0);
	buff_idx = 0;

	while (tmp_r) {
		void *addr;
		char **tmp;
		if (tmp_r->ai_family == AF_INET) {
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)tmp_r->ai_addr;
			tmp = realloc(buffer, sizeof(char *) * (buff_idx + 1));
			if (!tmp)
				return (0);
			buffer = tmp;
			buffer[buff_idx] = malloc(sizeof(char) * INET6_ADDRSTRLEN);

			inet_ntop(tmp_r->ai_family, &(ipv4->sin_addr), buffer[buff_idx], INET6_ADDRSTRLEN);
			printf("[ IPV4 ] -> %s\n", buffer[buff_idx]);
		} else {
			tmp = realloc(buffer, sizeof(char *) * (buff_idx + 1));
			if (!tmp)
				return (0);
			buffer = tmp;
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)tmp_r->ai_addr;
			inet_ntop(tmp_r->ai_family, &(ipv6->sin6_addr), buffer[buff_idx], INET6_ADDRSTRLEN);
			printf("[ IPV6 ] -> %s\n", buffer[buff_idx]);
		}
		tmp_r = tmp_r->ai_next;
		buff_idx++;
	}
	return 0;
}

int main(int argc, char **argv) {
	struct sockaddr_in *sock_addr;
	int sockfd;

	sock_addr = malloc(sizeof(struct sockaddr_in));
	sock_addr->sin_family = AF_INET;
	sock_addr->sin_port = htons(6767); 
	sock_addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	printf("%d\n", sock_addr->sin_addr.s_addr);

	inet_pton(AF_INET, "10.30.225.163", &sock_addr->sin_addr.s_addr);

	printf("%u\n", sock_addr->sin_addr.s_addr);

	if (argc == 2) {
		get_domain_ip_addr(argv[1]);
	}
	return 0;
}

