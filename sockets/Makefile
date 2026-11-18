
all: serv client

serv:
	cc server_socket.c -o server_socket

client:
	cc client_socket.c -o client_socket

clean:
	rm -rf server_socket client_socket

re: clean all
