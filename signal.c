#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * https://www.gnu.org/software/libc/manual/html_node/Handler-Returns.html#Handler-Returns
 */

/* The signal handler just clears the flag and re-enables itself. */
void catch_alarm(int sig)
{
  printf("Signal %i (%s) caught\n", sig, strsignal(sig));
  signal(sig, catch_alarm);
}

void do_stuff(void)
{
  sleep(2);
}

int main(void)
{
  // Termination Signals
  signal(SIGTERM, catch_alarm);
  signal(SIGQUIT, catch_alarm);
  signal(SIGKILL, catch_alarm);
  signal(SIGHUP, catch_alarm);
  signal(SIGINT, catch_alarm);

  // Job Control Signals
  signal(SIGSTOP, catch_alarm);
  signal(SIGUSR1, catch_alarm);
  signal(SIGUSR2, catch_alarm);

  printf("Started.\n");

  /* Check the flag once in a while to see when to quit. */
  while(1)
    do_stuff ();

  return EXIT_SUCCESS;
}
