/*
 * Modified from http://www.cim.mcgill.ca/~franco/OpSys-304-427/messages/node25.html
 *
 * 33333 is about 1/30th of a second
 */


#include <sys/time.h>
#include <signal.h>
#include <stdio.h>
#include <assert.h>

volatile int cnt=100;

void sigalrm(int sig) {
    extern volatile int cnt;
    cnt--;
    if (!(cnt % 10)) {
      fprintf(stderr,"%d...", cnt);
    }
}

int main(int argc, char* argv[])
{
    struct sigaction sa = {sigalrm, 0, 0, 0};
    struct itimerval iv = {{0, 33333}, {0, 33333}};

    assert(-1 != sigaction(SIGALRM, &sa, NULL));
    assert(-1 != setitimer(ITIMER_PROF, &iv, NULL));
    
    fprintf(stderr,"cnt=%d...", cnt);
    
    do /* nothing */; while (cnt);
    fprintf(stderr,"done - exit\n");
    return 0;
}
