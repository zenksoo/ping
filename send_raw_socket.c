#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int32_t get_domain_ip_addr(char *domain_name)
{
	return 0;
}

int main() {
	struct sockaddr_in *sock_addr;
	int sockfd;

	sock_addr = malloc(sizeof(struct sockaddr_in));
	sock_addr->sin_family = AF_INET;
	sock_addr->sin_port = htons(6767); 
	sock_addr->sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	printf("%d\n", sock_addr->sin_addr.s_addr);

	inet_pton(AF_INET, "10.30.225.163", &sock_addr->sin_addr.s_addr);

	printf("%d\n", ntohl(sock_addr->sin_addr.s_addr));
	return 0;
}

