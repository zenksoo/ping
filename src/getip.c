#include "ping.h"
#include <sys/socket.h>

void	getip(char *domain_name) {
	int				status;
	struct addrinfo	hints;
	struct addrinfo *res;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	status = getaddrinfo(domain_name, 0, &hints, &res);

}



