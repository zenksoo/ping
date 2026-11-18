## SOCKET

is an endpoint for communication between two programs, on the same machine or across a network. Think of it as a file descriptor for talking to another program. In Unix, “everything is a file”, so you read() and write() on a socket just like on a file

A socket is created using the socket() system call, which returns a file descriptor used
to refer to the socket in subsequent system calls:

    `fd = socket(domain, type, protocol);`

- **Communication domains**:
    -  The UNIX (AF_UNIX) domain allows communication between applications on
the same host. (POSIX.1g used the name AF_LOCAL as a synonym for AF_UNIX, but
this name is not used in SUSv3.)

    - The IPv4 (AF_INET) domain allows communication between applications running on hosts connected via an Internet Protocol version 4 (IPv4) network.

    - The IPv6 (AF_INET6) domain allows communication between applications running
on hosts connected via an Internet Protocol version 6 (IPv6) network.
Although IPv6 is designed as the successor to IPv4, the latter protocol is currently still the most widely used.

- **Socket types**

    Every sockets implementation provides at least two types of sockets: stream and
datagram. These socket types are supported in both the UNIX and the Internet
domains


    In the Internet domain, datagram sockets employ the User Datagram Protocol
(UDP), and stream sockets (usually) employ the Transmission Control Protocol (TCP).
Instead of using the terms Internet domain datagram socket and Internet domain stream
socket, we’ll often just use the terms **UDP socket** and **TCP socket**, respectively

Socket system calls
- The **socket()** system call creates a new socket.

- The **bind()** system call binds a socket to an address. Usually, a server employs
this call to bind its socket to a well-known address so that clients can locate
the socket.

- The **listen()** system call allows a stream socket to accept incoming connections
from other sockets.

- The **accept()** system call accepts a connection from a peer application on a listening stream socket, and optionally returns the address of the peer socket.

- The **connect()** system call establishes a connection with another socket

- Both sides exchange data with **send/recv** (or **read/write**).

- **close()** ends the connection. the connection end when program finished or keyboard interupt `CTL+C`

more details on : [CHAPETER 50 THE LINUX PROGRAMMING INTERFACE](https://broman.dev/download/The%20Linux%20Programming%20Interface.pdf)



| SERVER |  | CLIENT |
|--------|--------|--------|
| socket() | | socket() |
| bind() | (attach to port) | |
| listen() | (wait for calls) | |
| accept() | <--- connection --- | connect() |
| read()/recv() | <-------------> | write()/send() |
| close() | | close() |

## SERVER SIDE IMPLEMENTATION EXAMPLE

The server is a small TCP echo server. Its job is to create a socket, attach it to
port `6767`, wait for a client to connect, and send each received message back to
that client. It handles clients one at a time. Sending the text `close` tells the
server to send a final message and stop accepting new clients.

### 1. Create the server socket

```c
int server_fd = socket(AF_INET, SOCK_STREAM, 0);
```

`AF_INET` selects IPv4 and `SOCK_STREAM` selects a reliable TCP byte stream.
The returned file descriptor, `server_fd`, is the server's handle for socket
operations.

```c
int opt = 1;
setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
```

`SO_REUSEADDR` allows the program to reuse the port after a previous server
process has recently closed. This is useful during development and restarts.

### 2. Configure and bind the address

```c
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = INADDR_ANY;
addr.sin_port = htons(6767);
bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
```

`sockaddr_in` stores an IPv4 address and port. `INADDR_ANY` means that the
server accepts connections through any local network interface. `htons()`
converts the port from the host's byte order to network byte order. `bind()`
associates the socket with that local address, making port `6767` available to
the server.

### 3. Listen and accept connections

```c
listen(server_fd, 5);
client_fd = accept(server_fd, NULL, NULL);
```

`listen()` changes the socket into a listening socket. The `5` is the maximum
number of pending connections in the listening queue. `accept()` waits until a
client connects, then returns a new file descriptor for that client. The
original `server_fd` remains available for accepting future clients.

### 4. Receive and echo data

```c
while ((n = recv(client_fd, buf, sizeof(buf), 0)) > 0) {
    if (!strcmp(buf, "close")) {
        send(client_fd, "closing server...", strlen("closing server..."), 0);
        break;
    }
    send(client_fd, buf, n, 0);
}
```

`recv()` copies bytes from the client into `buf` and returns the number of
bytes received. For normal messages, `send()` writes those same bytes back,
which is why this is called an echo server. If the message is `close`, the
server replies with `closing server...` and exits its main loop. After a normal
client session, `close(client_fd)` releases that client's connection.

## CLIENT SIDE IMPLEMENTATION EXAMPLE

The client connects to the server at IPv4 address `127.0.0.1` (the local
machine) and port `6767`. It takes messages from the command line, sends them
to the server, receives the server's response, and prints both sides of the
conversation. For example, `./client_socket hello world` sends two messages.

### 1. Build the destination address

```c
sock_addr.sin_family = AF_INET;
sock_addr.sin_port = htons(6767);
inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr.s_addr);
```

The client fills the same address structure used by the server. The port must
match the server's port. `inet_pton()` converts the human-readable IPv4
address `127.0.0.1` into the binary form required by the socket API.

### 2. Create and connect the socket

```c
sockfd = socket(AF_INET, SOCK_STREAM, 0);
connect(sockfd, (struct sockaddr *)&sock_addr, sizeof(sock_addr));
```

The client creates an IPv4 TCP socket and calls `connect()`. TCP performs the
connection setup with the listening server. If the server is not running on
port `6767`, the connection fails.

### 3. Send command-line messages and read replies

```c
while (++i < argc) {
    send(sockfd, argv[i], sizeof(argv[i]), 0);
    recv(sockfd, buff, sizeof(buff) - 1, 0);
    printf("[ SERVER ] %s\n", buff);
}
```

`argc` and `argv` contain the arguments passed to the client program. Each
argument is sent to the server, and `recv()` waits for the server's response.
The response is then printed. With the current server implementation, normal
messages are echoed back.

### Run the example

Compile both programs from this directory:

```sh
make
```

Start the server in one terminal:

```sh
./server_socket
```

Start the client in another terminal:

```sh
./client_socket hello
./client_socket close
```

The first command demonstrates the echo response. The `close` message asks
the server to send `closing server...` and terminate.

> This is a learning example rather than production-ready networking code.
> A complete implementation should check the return value of every system
> call, handle partial sends and receives, ensure received data is
> null-terminated before using string functions, close the client socket, and
> use the actual message length when calling `send()`.
