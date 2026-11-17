#include "ping.h"

struct ipaddr *getip(char *domain_name) {
	int				status;
	struct addrinfo	hints;
	struct addrinfo *res;
	struct addrinfo *old_res;
	struct ipaddr	*ips;
	char			**tmp_buffer;


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	status = getaddrinfo(domain_name, 0, &hints, &res);
	if (status)
		return (display_messge(2, "Temporary failure in name resolution", UNKOWN_HOST), NULL);

	ips = malloc(sizeof(*ips));
	memset(ips, 0, sizeof(*ips));

	while (res) {
		if (res->ai_family == AF_INET) {
			if (!ips->ipv4_buffers)
				ips->ipv4_buffers = malloc(0);
			struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
			tmp_buffer = realloc(ips->ipv4_buffers, sizeof(char *) * (ips->ipv4_buff_size + 1));
			if (!tmp_buffer)
				return (NULL);
			ips->ipv4_buffers = tmp_buffer;
			ips->ipv4_buffers[ips->ipv4_buff_size] = malloc(sizeof(char) * INET_ADDRSTRLEN);

			inet_ntop(res->ai_family, &(ipv4->sin_addr), ips->ipv4_buffers[ips->ipv4_buff_size], INET_ADDRSTRLEN);
			ips->ipv4_buff_size++;
		} else if (res->ai_family == AF_INET6) {
			if (!ips->ipv6_buffers)
				ips->ipv6_buffers = malloc(0);
			struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
			tmp_buffer = realloc(ips->ipv6_buffers, sizeof(char *) * (ips->ipv6_buff_size + 1));
			if (!tmp_buffer)
				return (NULL);
			ips->ipv6_buffers = tmp_buffer;
			ips->ipv6_buffers[ips->ipv6_buff_size] = malloc(sizeof(char) * INET6_ADDRSTRLEN);

			inet_ntop(res->ai_family, &(ipv6->sin6_addr), ips->ipv6_buffers[ips->ipv6_buff_size], INET6_ADDRSTRLEN);
			ips->ipv6_buff_size++;
		}
		old_res = res;
		res = res->ai_next;
		free(old_res);
	}
	return (ips);
}
