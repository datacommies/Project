#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>

#define INTERVAL 33333

void set_alarm();

void alarm_wakeup (int i)
{
   signal(SIGALRM,alarm_wakeup);

   printf(".");
   fflush(stdout);

   set_alarm();
}

void set_alarm ()
{
  struct itimerval tout_val;
  
  tout_val.it_interval.tv_sec = 0;
  tout_val.it_interval.tv_usec = 0;
  tout_val.it_value.tv_sec = 0;
  tout_val.it_value.tv_usec = INTERVAL; /* set time for interval (1/30th of a second) */
  setitimer(ITIMER_REAL, &tout_val,0);

  signal(SIGALRM,alarm_wakeup); /* set the Alarm signal capture */
  
}

int main() {

  set_alarm();
  while (1) 
    ;

  return 0;
}
