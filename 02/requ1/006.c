 #include <stdio.h>
 #include <unistd.h>
 #include <time.h>
 
 double get_current_timecount() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec*1e-9;
 }
 
 int main( int argc, char* argv[] ) {
    double t1 = get_current_timecount();

         FILE* fpr;
         FILE* fpw;
         int ret;
         int bufsize = 64;
         char buf[bufsize];
 
         if(argc != 2) {
                 printf("usage: %s [filename]\n", argv[0]);
                 exit(-1);
         }
 
         fpr = fopen(argv[1], "r");
         fpw = fopen("tmp.txt", "w");
 
         ret = fread(buf, sizeof(char), bufsize, fpr);
         while (ret > 0) {
                 fwrite(buf, sizeof(char), ret, fpw);
                 ret = fread(buf, sizeof(char), bufsize, fpr);
         }
         fclose(fpr);
         fclose(fpw); 
 
    double t2 = get_current_timecount();
    printf("%lf\n", t2-t1);
    return 0;
 }