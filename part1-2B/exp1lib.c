#include "exp1.h"
#include "exp1lib.h"
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int exp1_tcp_listen(const char* port) {

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	int errcode = 0;
	struct addrinfo* res;
	if ((errcode = getaddrinfo(NULL, port, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo():%s\n", gai_strerror(errcode));
		return (-1);
	}

	int sock = 0;
	sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock == -1) {
		perror("socket");
		freeaddrinfo(res);
		return (-1);
	}

	int socket_option = 1;
	socklen_t socket_option_size = sizeof(socket_option);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &socket_option,
			socket_option_size) == -1) {
		perror("setsockopt");
		close(sock);
		freeaddrinfo(res);
		return (-1);
	}

	int binderr = bind(sock, res->ai_addr, res->ai_addrlen);
	if (binderr == -1) {
		perror("bind");
		close(sock);
		freeaddrinfo(res);
		return (-1);
	}

	int listenerr = listen(sock, SOMAXCONN);
	if (listenerr == -1) {
		perror("listen");
		close(sock);
		freeaddrinfo(res);
		return (-1);
	}
	freeaddrinfo(res);
	return (sock);
}

int exp1_tcp_connect(const char *hostname, const char* port) {

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	struct addrinfo* res = NULL;
	int errcode = 0;
	errcode = getaddrinfo(hostname, port, &hints, &res);
	if (errcode != 0) {
		fprintf(stderr, "getaddrinfo():%s\n", gai_strerror(errcode));
		return (-1);
	}

	int soc = 0;
	soc = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (soc == -1) {
		perror("socket");
		freeaddrinfo(res);
		return (-1);
	}

	int connerr = 0;
	connerr = connect(soc, res->ai_addr, res->ai_addrlen);
	if (connerr == -1) {
		perror("connect");
		close(soc);
		freeaddrinfo(res);
		return (-1);
	}

	freeaddrinfo(res);
	return (soc);
}

