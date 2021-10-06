#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
//#include<sys/loctl.h>

#define MAX_SIZE 1024

int main()
{
	int fd=open("/dev/my_hello",O_RDWR);
	return 0;
	close(fd);
}

