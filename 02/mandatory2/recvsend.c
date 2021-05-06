#include "exp1.h"
#include "exp1lib.h"
#include <stdio.h>
#include <unistd.h>
#include <time.h>

double get_current_timecount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec*1e-9;
}
 

int main(int argc, char** argv) {
	double t1 = get_current_timecount();

	int sock;
	char buf[1024];
	FILE* fp;
	int ret;

	if(argc != 3) {
		printf("usage: %s [ip address] [filename]\n", argv[0]);
		exit(-1);
	}

	sock = exp1_tcp_connect(argv[1], 11111);
	fp = fopen(argv[2], "r");
	ret = recv(sock, buf, 1024, 0);
	while(ret > 0) {
		send(sock, buf, ret, 0);
		ret = recv(sock, buf, 1024, 0);
	}
	close(sock);

    double t2 = get_current_timecount();
    printf("%lf\n", t2-t1);
    return 0;
}

