#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char **argv) {
	struct sockaddr_in	sock_addr;
	char				**stripaddr;
	int					sockfd;
	int 				i;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(6767);
	inet_pton(AF_INET, "10.12.4.12", &sock_addr.sin_addr.s_addr);

	printf("%u\n", sock_addr.sin_addr.s_addr);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(sockfd, (struct sockaddr *)&sock_addr, sizeof(sock_addr)))
		return (1);

	i = 0;
	char buff[1024] = {0};
	while (++i < argc) {
		printf("[ CLIENT ] %s\n", argv[i]);
		memset(buff, 0, sizeof(buff));
		send(sockfd, argv[i], sizeof(argv[i]), 0);
		recv(sockfd, buff, sizeof(buff) - 1, 0);
		printf("[ SERVER ] %s\n", buff);
	}
	return 0;
}

