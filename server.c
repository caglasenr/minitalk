#include <signal.h>
#include <unistd.h>
void server_handler(int sig, siginfo_t *info, void *ucontext)
{
    (void)ucontext;
    (void)info;

    static int bit = 0;
    static unsigned char current = 0;
    if(sig == SIGUSR1)
        current &= ~(1 << (7-bit));
    else if(sig == SIGUSR2)
        current |=(1 << (7-bit));
    bit++;
    if(bit==8)
    {
        write(1,&current,1);
        bit =0;
        current = 0;
    }

}
int main(int ac,char* av[])
{
    struct  sigaction sa;
    sa.sa_sigaction = server_handler;
    sa.sa_flags=SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    
    pid_t pid = getpid();
    char buf[20];
    int len =0;

    while(pid)
    {
        buf[len]= (pid%10)+'0';
        pid /=10;
        len++;
    }
    while(len--)
        write(1,&buf[len],1);
    write(1,"\n",1);
    sigaction(SIGUSR1,&sa,NULL);
    sigaction(SIGUSR2,&sa,NULL);

    while(1)
        pause();
    return 0;

}