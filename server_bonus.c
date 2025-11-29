#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void server_handler(int sig, siginfo_t *info, void *ucontext)
{
    (void)ucontext;
    (void)info;

    static int bit = 0;
    static unsigned char current = 0;
    if(sig == SIGUSR2)
        current = (current << 1) | 1;
    else if(sig == SIGUSR1)
        current = (current << 1);
    bit++;

    
    if(bit==8)
    {
        write(1,&current,1);
        bit =0;
        current = 0;
    }
    kill(info->si_pid,SIGUSR1);

}
int main(int ac,char* av[])
{
    (void)ac;
    (void)av;
    struct  sigaction sa;
    sa.sa_sigaction = server_handler;
    sa.sa_flags=SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    printf("Server PID: %d\n", getpid());
    sigaction(SIGUSR1,&sa,NULL);
    sigaction(SIGUSR2,&sa,NULL);
    while(1)
        pause();
    return 0;

}