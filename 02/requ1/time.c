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
 
    // do something
    sleep(3);
 
    double t2 = get_current_timecount();
    printf("%lf\n", t2-t1);
    return 0;
 }