#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int main(int ac,char* av[])
{
    if(ac != 3)
        return 0;
    int server_pid=atoi(av[1]);
    char *msg = av[2];
    int i;
    while(*msg)
    {
        unsigned char c = *msg;
        i = 7;
        while(i >= 0)
        {
            if((c>>i) & 1)
                kill(server_pid,SIGUSR2);
            else
                kill(server_pid,SIGUSR1);
            i--;
            usleep(1000);
        }
        msg++;
    }
    unsigned char c = '\0';
    i = 7;
    while(i>=0)
    {
        if((c >> i) & 1)
            kill(server_pid, SIGUSR2);
        else
            kill(server_pid, SIGUSR1);
        i--;
        usleep(1000);
    }
    return 0;
}