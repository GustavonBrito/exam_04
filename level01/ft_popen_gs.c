#include <unistd.h>
#include <stdlib.h>

static void close_fd(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}

int popen(const char *file, char *const argv[], char type)
{
    
}