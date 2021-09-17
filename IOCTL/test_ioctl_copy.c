#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
//#include <sys/types.h>
#include<sys/ioctl.h>//for IOCTL macros and definition of ioctl()
#include<errno.h>// for printing error numbers.

#define MY_MAGIC 'a'// Magic Number.
#define WR_VALUE _IOW(MY_MAGIC,'a',int32_t*)//IOCTL command
#define RD_VALUE _IOR(MY_MAGIC,'b',int32_t*)//IOCTL command
//#define MY_IOCTL_MAX_CMD 2

int main()
{
	int fd;
        int32_t value,number;	
	
	//int res;
	
	printf("[%d] - Opening device my_cdrv\n", getpid() );
	
	fd = open( "/dev/my_Ioctl_driver", O_RDWR );/*Open FILE and return a new file descriptor for it, or -1 on error.
   							OFLAG determines the type of access used.  If O_CREAT or O_TMPFILE is set
   							in OFLAG, the third argument is taken as a `mode_t', the mode of the
   							created file.*/
   	//fd = open( "/dev/my_lsdkjfgls", O_RDWR );
	if( fd < 0 ) {
		printf("\n\nDevice could not be opened\n\n");
		printf("%d %s\n",errno,strerror(errno));

		return errno;;
	}
	printf("Device opened with ID [%d]\n", fd);
	
	   
	printf("Enter the Value to send\n");
	scanf("%d",&number);
	printf("Writing Value to Driver\n");
	if((ioctl(fd, WR_VALUE, (int32_t*) &number) < 0))//return 0 or non -ve value on success or else -1 will return and errno will set appropriately.
	{
		printf("%d %s",errno,strerror(errno));
		return errno;
	}
	 
	printf("Reading Value from Driver\n");
	if((ioctl(fd, RD_VALUE, (int32_t*) &value)<0))
	{
		printf("%d %s",errno,strerror(errno));
		return errno;	
	}
	
	printf("Value is %d\n", value);

	printf("Closing Driver\n");
	if((close(fd)<0))
	{
		printf("%d %s",errno,strerror(errno));
		return errno;
	}
	
	
	
	exit(0);
}


