 #include <stdio.h>
 #include <unistd.h>
 #include <time.h>
 #include <stdlib.h>
 #include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

 double get_current_timecount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec*1e-9;
 }
 
 int main( int argc, char* argv[] ) {

         int fpr;
         int fpw;
         int ret;
         int bufsize =4;
         char buf[bufsize];
 
         if(argc != 2) {
                 printf("usage: %s [filename]\n", argv[0]);
                 exit(-1);
         }
 
         fpr = open(argv[1], O_RDONLY);
         fpw = open("tmp.txt",  O_WRONLY);
 

    double t1 = get_current_timecount();
         ret = read(fpr, buf, bufsize);
          while (ret > 0) {
                 write(fpw, buf , ret);
                 ret = read(fpr,buf, bufsize);
        }
    double t2 = get_current_timecount();
    printf("%lf\n", t2-t1);
         close(fpr);
         close(fpw); 
 
    return 0;
 }