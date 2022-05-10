/*
Name :          ACHINT JAIN
G-Number :      G01324710
*/

#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <unistd.h>

int cs531_system(char *s){

    pid_t child, w; 
    int status;
    sig_t prev_sig;
    
    //below check is to stop the further excution if the command line argument is absent.
    if (s == NULL)
    {
       printf("\nERROR: Command missing....\n");
       return -1;
    }
    
    //forking the following process to make parent and child process
    child = fork();

    //handling if fork function fails
    if (child == -1) {
        perror("fork error");
        exit(EXIT_FAILURE); 
    }


//child process
if (child == 0) { 
    /* child process */
    int tt = open("/dev/tty", O_RDWR);
    close(1); 
    dup(tt); 
    execlp("sh", "sh","-c", s, (char *)NULL);
} 
else 
{ /* Parent process*/

    //catching the previous state of parent process (original)
    prev_sig = signal(SIGINT,SIG_IGN); // SIGINT registration
    signal(SIGQUIT,SIG_IGN);
    do {
        w = waitpid(child, &status, WUNTRACED | WCONTINUED); //this will wait for child to terminate and remove all its components from memory.
        if (w == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE); 
        }
        if (WIFEXITED(status)) {
            printf("exited, status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("killed by signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("stopped by signal %d\n", WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) 
        { 
            printf("continued\n");
        }
    } 
    while (!WIFEXITED(status) && !WIFSIGNALED(status)); //run this while untill child does not exit
    

    //Re-instating the behavior to its original state.
    signal(SIGINT,prev_sig);
    signal(SIGQUIT,prev_sig);
}

return 0;
}

int main(int argc, char *argv[]) 
{ 
    int status;
    status = cs531_system(argv[1]); 
    printf("\nParent process is sleeping...\n"); 
    sleep(10);
    return argc;
}