#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(void)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;   // all interfaces
    addr.sin_port = htons(6767);         // host -> network byte order

    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(addr)))
        return (1);
    listen(server_fd, 5);
    printf("Listening on port 6767...\n");

    int client_fd;
    while (1) {
        client_fd = accept(server_fd, NULL, NULL);

        printf("%d\n", client_fd);

        char buf[1024];
        ssize_t n;
        while ((n = recv(client_fd, buf, sizeof(buf), 0)) > 0) {
            if (!strcmp(buf, "close"))
            {
                send(client_fd, "closing server...", strlen("closing server..."), 0);
                break;
            } else
                send(client_fd, buf, n, 0);
        }
        if (!strcmp(buf, "close"))
            break;
        close(client_fd);
    }
    close(client_fd);
    close(server_fd);
    return 0;
}
