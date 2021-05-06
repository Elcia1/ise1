#include "exp1.h"
 #include <stdio.h>
 #include <unistd.h>
 #include <time.h>
 
 double get_current_timecount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec*1e-9;
 }

int main(int argc, char** argv) {
	FILE* fpr;
	FILE* fpw;
	int ret;
	int bufnum = 4;
	
	while(bufnum  < 4097){



	char buf[bufnum];

	if(argc != 2) {
		printf("usage: %s [filename]\n", argv[0]);
		exit(-1);
	}

	fpr = fopen(argv[1], "r");
	fpw = fopen("tmp.txt", "w");

    double t1 = get_current_timecount();
	ret = fread(buf, sizeof(char), bufnum, fpr);
	while (ret > 0) {
		fwrite(buf, sizeof(char), ret, fpw);
		ret = fread(buf, sizeof(char), bufnum, fpr);
	}
	double t2 = get_current_timecount();
    printf("%lf\n", t2-t1);

	fclose(fpr);
	fclose(fpw);

	bufnum *= 4;

	}
	return 0;
}
