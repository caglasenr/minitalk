#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
volatile sig_atomic_t g_ack = 0;
void ack_handler(int sig)
{
    (void)sig;
    g_ack = 1;
}
void send_char(int server_pid, unsigned char c) // 0100 0001
{
    int i = 7;
    while(i >= 0)
    {
        if((c >> i) & 1)
            kill(server_pid,SIGUSR2);
        else
            kill(server_pid,SIGUSR1);
        while(!g_ack)
           pause() ;
        g_ack = 0;
        i--;
    }
}
void send_message(int server_pid, const char *str)
{
    int i=0;
    while(str[i]!= '\0')
    {
        send_char(server_pid,str[i]);
        i++;
    }
    send_char(server_pid,'\0');

}
int main(int ac,char* av[])
{
    if(ac != 3)
        return 0;
    
    int server_pid=atoi(av[1]);
    char *msg = av[2];
    struct sigaction sa;
    
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1,&sa,NULL);
    send_message(server_pid,msg);
    return 0;
}